//
// Created by jmmar on 09/05/2024.
//

#ifndef AGENTS_H
#define AGENTS_H

#include <memory>

#include "AgentAttributes.h"
#include "Agent.h"

class Agents {
public:
    Agents(int numOfAgents, std::map<std::string, int> agentIndexes, std::unique_ptr<Agent[]> agentArray);
    void runTick();

private:
    int numOfAgents_m{};
    std::map<std::string, int> agentIndexes_m;
    std::unique_ptr<Agent[]> agentArray_m;
};



#endif //AGENTS_H
