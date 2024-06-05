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

class Agent;

class Agents {
public:
    Agents(int numOfAgents, std::map<std::string, int> agentIndexes, std::vector<Agent> agentVector);
    [[nodiscard]] int getNumberOfAgents() const;
    Agent getAgentByIndex(int agentIndex);
    Agent getAgentByName(const std::string& agentName);
    void runTick();

private:
    int numOfAgents_m;
    std::map<std::string, int> agentIndexes_m;
    std::vector<Agent> agentVector_m;
};



#endif //AGENTS_H
