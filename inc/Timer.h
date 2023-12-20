#ifndef TIMER_H__
#define TIMER_H__

#pragma once

#include <functional>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unordered_map>
#include <set>
#include <vector>


class Timer {
public:
    Timer(std::function<void()> callback, unsigned long long time_ms, bool periodic = false);
    bool isPeriodic() const;
    void reschedule();
    std::chrono::steady_clock::time_point getNextExecutionTime() const;

    void executeCallback() const;

    // Disallow copy operations
    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;

    // Allow move operations
    Timer(Timer&&) noexcept;
    Timer& operator=(Timer&&) noexcept;

private:
    void calculateNextExecutionTime();
    std::function<void()> callback;
    unsigned long long time_ms;
    std::chrono::steady_clock::time_point nextExecutionTime;
    bool periodic;
};

#endif