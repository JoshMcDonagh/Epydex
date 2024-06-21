//
// Created by Joshua McDonagh on 13/05/2024.
//

#ifndef AGENT_H
#define AGENT_H

#include <string>
#include "AgentAttributes.h"
#include "AgentResults.h"

class Agents;

class Agent {
public:
    Agent(std::string &name, AgentAttributes physiology, AgentAttributes behaviour, const AgentResults &agentResults);
    [[nodiscard]] AgentAttributes getPhysiology() const;  // Added const
    [[nodiscard]] AgentAttributes getBehaviour() const;   // Added const
    [[nodiscard]] AgentResults getResults() const;        // Added const
    void runTick(const Agents* agents);

private:
    std::string name_m;
    AgentAttributes physiology_m;
    AgentAttributes behaviour_m;
    AgentResults agentResults_m;
};

#endif //AGENT_H
