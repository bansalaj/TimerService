#pragma once

#include "Timer.h"
#include "ThreadPool.h"

class TimerManager {
public:
    TimerManager(size_t numberOfthreads = 4);
    ~TimerManager();

    int addTimer(std::function<void()> callback, unsigned long long time_ms,
                    bool periodic);
    void removeTimer(const int& id);

    int getTimersCount();

private:
    std::set<std::pair<std::chrono::steady_clock::time_point, int>> timerQueue;
    std::unordered_map<int, Timer> timers;
    std::mutex mtx;
    std::condition_variable cv;
    std::thread mgmtThread;
    bool active;
    ThreadPool threadPool;

    void mgmtFunction();
    int generateUniqueId();

};
