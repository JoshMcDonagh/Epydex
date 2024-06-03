//
// Created by Joshua McDonagh on 09/05/2024.
//

#include "../include/Model.h"

ModelResults run(
    int const numOfCores,
    bool const areTempFilesCleanedUp,
    Clock const clock,
    Agents agents,
    ModelResults const results) {


    while (!clock.isFinished()) {
        agents.runTick();
    }

    return results;
}

