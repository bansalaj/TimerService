#include "gtest/gtest.h"
#include "Timer.h"
#include "TimerManager.h"


// Test to check if Timer correctly identifies as periodic
TEST(TimerTest, PeriodicTimerCheck) {
    Timer timer([](){}, 1000, true);
    EXPECT_TRUE(timer.isPeriodic());
}

TEST(TimerTest, OneShotTimerCheck) {
    Timer timer([](){}, 1000, false);
    EXPECT_FALSE(timer.isPeriodic());
}

TEST(TimerManagerTest, TimerRegistrationTest) {
    TimerManager manager;
    manager.addTimer([](){}, 1000, false);
    manager.addTimer([](){}, 2000, true);

    EXPECT_EQ(manager.getTimersCount(), 2);
}

TEST(TimerManagerTest, TimerRemovalTest) {
    TimerManager manager;
    int timerId1 = manager.addTimer([](){}, 1000, false);
    int timerId2 = manager.addTimer([](){}, 2000, true);

    manager.removeTimer(timerId1);
    EXPECT_EQ(manager.getTimersCount(), 1);

    manager.removeTimer(timerId2);
    EXPECT_EQ(manager.getTimersCount(), 0);
}

TEST(TimerManagerTest, OneShotTimerExecutionTest) {
    std::atomic<bool> callbackCalled(false);

    TimerManager manager;
    manager.addTimer([&callbackCalled](){ callbackCalled = true;}, 100, false);

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    EXPECT_TRUE(callbackCalled);
}

TEST(TimerManagerTest, PeriodicTimerExecutionTest) {
    std::atomic<int> callbackCount(0);

    TimerManager manager;

    manager.addTimer([&callbackCount]() { callbackCount++;}, 50, true);

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    EXPECT_GT(callbackCount.load(), 1);
}