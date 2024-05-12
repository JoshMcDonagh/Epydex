//
// Created by jmmar on 09/05/2024.
//

#include "../include/Agents.h"

Agents::Agents(int numOfAgents, std::unique_ptr<std::string[]> agentNames, const AgentAttributes& agentAttributes) : agentAttributes_m(agentAttributes){
    numOfAgents_m = numOfAgents;
    propertiesTableSize_m = agentAttributes_m.getNumOfProperties() + 1;
    propertiesTable_m.reset(new std::vector<std::variant<int, double,
        std::string, bool>>[propertiesTableSize_m]);

    for (int i = 0; i < propertiesTableSize_m; i++) {
        std::vector<std::variant<int, double,std::string, bool>> column_vector = propertiesTable_m[i];
        for (int j = 0; j < numOfAgents; j++) {
            std::string agentName = agentNames[j];
            if (i == 0) {
                column_vector.emplace_back(agentName);
                agentIndexes_m[agentName] = j;
            }
            else {
                column_vector.push_back(agentAttributes_m.getPropertyByIndex(i - 1).getStartingValue());
            }
        }
    }
}

AgentAttributes Agents::getAgentAttributes() {
    return agentAttributes_m;
}


void Agents::runTick() {

}
