//
// Created by jmmar on 09/05/2024.
//

#ifndef AGENTS_H
#define AGENTS_H
#include <string>
#include <variant>

#include "AgentAttributes.h"


class Agents {
public:
    explicit Agents(const AgentAttributes& agentAttributes);
    AgentAttributes getAgentAttributes();
    void runTick();

private:
    AgentAttributes agentAttributes_m;
};



#endif //AGENTS_H
