//
// Created by jmmar on 09/05/2024.
//

#include <utility>

#include "../include/Agents.h"

Agents::Agents(int numOfAgents, std::map<std::string, int> agentIndexes, std::unique_ptr<Agent[]> agentArray) {
    numOfAgents_m = numOfAgents;
    agentIndexes_m = std::move(agentIndexes);
    agentArray_m = std::move(agentArray);
}

void Agents::runTick() {
    for (int i = 0; i < numOfAgents_m; i++)
        agentArray_m[i].runTick(this);
}
