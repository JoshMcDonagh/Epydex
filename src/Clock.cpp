//
// Created by Joshua McDonagh on 09/05/2024.
//

#include "../include/Clock.h"

Clock::Clock(int const totalNumOfTicksToRun, int const numOfWarmUpTicks) {
    totalNumOfTicksToRun_m = totalNumOfTicksToRun;
    numOfWarmUpTicks_m = numOfWarmUpTicks;
    currentTick_m = 0;
}

int Clock::getTotalNumberOfTicksToRun() const {
    return totalNumOfTicksToRun_m;
}

bool Clock::isFinished() const {
    return currentTick_m < totalNumOfTicksToRun_m + numOfWarmUpTicks_m;
}

void Clock::tick() {
    currentTick_m += 1;
}
