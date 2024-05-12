//
// Created by jmmar on 09/05/2024.
//

#include "../include/Agents.h"

Agents::Agents(const AgentAttributes& agentAttributes) : agentAttributes_m(agentAttributes){

}

AgentAttributes Agents::getAgentAttributes() {
    return agentAttributes_m;
}


void Agents::runTick() {

}
