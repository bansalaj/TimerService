#include "TimerManager.h"


/**
 * Constructor
*/
TimerManager::TimerManager() : active(true) {
    mgmtThread = std::thread(&TimerManager::mgmtFunction, this);
}

/**
 * Destructor
*/
TimerManager::~TimerManager() {
    active = false;
    cv.notify_all();
    if (mgmtThread.joinable()) {
        mgmtThread.join();
    }
}

/**
 * addTimer
 *  Adds Timer object to the queue
*/
void TimerManager::addTimer(const Timer& timer) {
    std::lock_guard<std::mutex> lock(mtx);
    // Add the timer to the queue

    cv.notify_one(); // Wake up the management thread if it is waiting
}

/**
 * removeTimer
 *  removes Timer object from the queue
*/
void TimerManager::removeTimer(const Timer& timer) {
    std::lock_guard<std::mutex> lock(mtx);

    cv.notify_one();
}

void TimerManager::mgmtFunction() {
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock);

    while (active) {
        lock.lock();

        auto now = std::chrono::steady_clock::now();
        while(!timerQueue.empty() && timerQueue.begin()->first <= now) {
            int id = timerQueue.begin()->second;
            auto& timer = timers[id];

            // Asynchronous execution of the callback
            std::thread callbackThread(&Timer::executeCallback, &timer);
            callbackThread.detach();

            if (timer.isPeriodic()) {
                // update the timer's next execution time
                timer.reschedule();
                timerQueue.emplace(timer.getNextExecutionTime(), id);
            } else {
                timers.erase(id);
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