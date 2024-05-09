//
// Created by jmmar on 09/05/2024.
//

#include "../include/Clock.h"

Clock::Clock(int const totalNumOfTicksToRun, int const numOfWarmUpTicks) {
    totalNumOfTicksToRun_m = totalNumOfTicksToRun;
    numOfWarmUpTicks_m = numOfWarmUpTicks;
}

int Clock::getTotalNumberOfTicksToRun() const {
    return totalNumOfTicksToRun_m;
}
