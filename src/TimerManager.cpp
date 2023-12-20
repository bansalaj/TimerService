#include "TimerManager.h"


/**
 * Constructor
*/
TimerManager::TimerManager(size_t numOfThreads) : threadPool(numOfThreads) ,active(true) {
    mgmtThread = std::thread(&TimerManager::mgmtFunction, this);
}

/**
 * Destructor
*/
TimerManager::~TimerManager() {
    active = false;
    cv.notify_one();
    if (mgmtThread.joinable()) {
        mgmtThread.join();
    }
}

/**
 * addTimer
 *  Adds Timer object to the queue
*/
int
TimerManager::addTimer(std::function<void()> callback, unsigned long long time_ms,
                            bool periodic) {
    std::lock_guard<std::mutex> lock(mtx);
    // Add the timer to the queue
    int id = generateUniqueId();
    auto result = timers.emplace(std::piecewise_construct,
                                std::forward_as_tuple(id),
                                std::forward_as_tuple(callback, time_ms, periodic)
                                );

    timerQueue.emplace(result.first->second.getNextExecutionTime(), id);

    cv.notify_one(); // Wake up the management thread if it is waiting
    return id;
}

/**
 * removeTimer
 *  removes Timer object from the queue
*/
void
TimerManager::removeTimer(const int &timerId) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = timers.find(timerId);
    if (it != timers.end()) {
        // Remove the timers from the map of iterators
        timers.erase(it);

        // Also remove the time from the queue if it's there
        for (auto queueIt = timerQueue.begin(); queueIt != timerQueue.end(); ++queueIt) {
            if (queueIt->second == timerId) {
                timerQueue.erase(queueIt);
                break; // Exit the loop once the timer is found and removed
            }
        }
    }

    // notify the management function in case it's waiting for the next timer
    cv.notify_one();
}


int
TimerManager::getTimersCount() {
    std::lock_guard<std::mutex> lock(mtx);
    return timers.size();
}

void
TimerManager::mgmtFunction() {
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock);

    while (active) {
        lock.lock();

        auto now = std::chrono::steady_clock::now();
        while(!timerQueue.empty() && timerQueue.begin()->first <= now) {
            int id = timerQueue.begin()->second;
            timerQueue.erase(timerQueue.begin()); // Remove the current timer from the queue

            auto timerIt = timers.find(id);
            if (timerIt != timers.end()) {
                auto& timer = timerIt->second;

                // Asynchronous execution of the callback
                threadPool.enqueue([&timer] {
                    //auto& timer = timerIt->second;
                    timer.executeCallback();
                });

                if (timer.isPeriodic()) {
                    // update the timer's next execution time
                    timer.reschedule();
                    timerQueue.emplace(timer.getNextExecutionTime(), id);
                } else {
                    timers.erase(timerIt);
                }
            } else {
                // Timer not found, remove it from queue
                timerQueue.erase(timerQueue.begin());
            }
        }

        if (!timerQueue.empty()) {
            // Calculate the wait duration for the next timer and wait
            auto nextTimerDuration = timerQueue.begin()->first - std::chrono::steady_clock::now();
            cv.wait_for(lock, nextTimerDuration, [this]{ return !active;});
        } else if (active) {
            // if the queue is empty, wait until a new timer is added
            cv.wait(lock, [this]{ return !active || !timerQueue.empty();});
        }

        lock.unlock(); // unlock the mutex
    }
}


/**
 * generateUniqueId
 *  generates unique Id
*/
int
TimerManager::generateUniqueId() {
    static int id = 0;
    return ++id;
}