//
// Created by Joshua McDonagh on 09/05/2024.
//

#include "../include/Model.h"

std::vector<AgentResults> run(int const numOfCores, bool const areTempFilesCleanedUp, Clock clock, Agents agents) {
    while (!clock.isFinished()) {
        agents.runTick();
        clock.tick();
    }

    std::vector<AgentResults> results;
    for (int i = 0; i < agents.getNumberOfAgents(); i++)
        results.push_back(agents.getAgentByIndex(i).getResults());

    return results;
}

