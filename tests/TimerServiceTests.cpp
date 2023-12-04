#include "gtest/gtest.h"
#include "Timer.h"


// Test to check if Timer correctly identifies as periodic
TEST(TimerTest, PeriodicTimerCheck) {
    Timer timer([](){}, 1000, true);
    EXPECT_TRUE(timer.isPeriodic());
}

TEST(TimerTest, OneShotTimerCheck) {
    Timer timer([](){}, 1000, false);
    EXPECT_FALSE(timer.isPeriodic());
}