//
// Created by Joshua McDonagh on 05/06/2024.
//

#include <gtest/gtest.h>
#include "../include/Clock.h"  // Adjust the include path if necessary

// Test fixture for Clock tests
class ClockTest : public ::testing::Test {
protected:
    Clock* clock{};

    void SetUp() override {
        // You can initialize your Clock object here with specific parameters
        clock = new Clock(10, 5);
    }

    void TearDown() override {
        // Clean up any resources
        delete clock;
    }
};

// Test for constructor and getTotalNumberOfTicksToRun()
TEST_F(ClockTest, ConstructorAndTotalTicksTest) {
    EXPECT_EQ(clock->getTotalNumberOfTicksToRun(), 10);
}

// Test for isFinished() method before and after ticks
TEST_F(ClockTest, IsFinishedTest) {
    // Initially, it should not be finished
    EXPECT_FALSE(clock->isFinished());

    // Tick the clock 15 times (10 total ticks + 5 warm-up ticks)
    for (int i = 0; i < 15; ++i) {
        clock->tick();
    }

    // After 15 ticks, it should be finished
    EXPECT_TRUE(clock->isFinished());
}

// Test for tick() method and currentTick_m tracking
TEST_F(ClockTest, TickMethodTest) {
    // Tick the clock 5 times
    for (int i = 0; i < 5; ++i) {
        clock->tick();
    }

    // After 5 ticks, it should still not be finished
    EXPECT_FALSE(clock->isFinished());

    // Tick the clock 10 more times
    for (int i = 0; i < 10; ++i) {
        clock->tick();
    }

    // After 15 ticks in total, it should be finished
    EXPECT_TRUE(clock->isFinished());
}
