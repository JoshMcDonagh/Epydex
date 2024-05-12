//
// Created by jmmar on 09/05/2024.
//

#ifndef AGENTS_H
#define AGENTS_H

#include <memory>

#include "AgentAttributes.h"


class Agents {
public:
    explicit Agents(int numOfAgents, std::unique_ptr<std::string[]> agentNames, const AgentAttributes& agentAttributes);
    AgentAttributes getAgentAttributes();
    void runTick();

private:
    int numOfAgents_m;
    AgentAttributes agentAttributes_m;
    std::map<std::string, int> agentIndexes_m;
    int propertiesTableSize_m;
    std::unique_ptr<std::vector<std::variant<int, double, std::string, bool>>[]> propertiesTable_m;
};



#endif //AGENTS_H
