//
// Created by Joshua McDonagh on 09/05/2024.
//

#ifndef AGENTS_H
#define AGENTS_H

#include <memory>
#include <vector>
#include <map>
#include <string>

#include "AgentAttributes.h"
#include "Agent.h"

class Agents {
public:
    Agents(int numOfAgents, std::map<std::string, int> agentIndexes, std::vector<Agent> agentVector);
    void runTick();

private:
    int numOfAgents_m;
    std::map<std::string, int> agentIndexes_m;
    std::vector<Agent> agentVector_m;
};



#endif //AGENTS_H
