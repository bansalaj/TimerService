#ifndef TIMERMANAGER_H__
#define TIMERMANAGER_H__

#include "Timer.h"

class TimerManager {
public:
    TimerManager();
    ~TimerManager();

    void addTimer(const Timer& timer);
    void removeTimer(const Timer& timer);

private:
    std::set<std::pair<std::chrono::steady_clock::time_point, int>> timerQueue;
    std::unordered_map<int, Timer> timers;
    std::mutex mtx;
    std::condition_variable cv;
    std::thread mgmtThread;
    bool active;

    void mgmtFunction();

};

#endif