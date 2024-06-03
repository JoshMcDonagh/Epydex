//
// Created by Joshua McDonagh on 09/05/2024.
//

#include <utility>

#include "../include/Agents.h"

Agents::Agents(int numOfAgents, std::map<std::string, int> agentIndexes, std::vector<Agent> agentVector) {
    numOfAgents_m = numOfAgents;
    agentIndexes_m = std::move(agentIndexes);
    agentVector_m = std::move(agentVector);
}

void Agents::runTick() {
    for (int i = 0; i < numOfAgents_m; i++)
        agentVector_m[i].runTick(this);
}
