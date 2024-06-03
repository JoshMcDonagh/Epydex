//
// Created by Joshua McDonagh on 29/05/2024.
//

#include "../include/AgentGenerator.h"

AgentGenerator::AgentGenerator(GenerateAgentFunc generateAgentFunc,
                               PropertyFactories propertyFactories,
                               EventFactories eventFactories) {
    generateAgentFunc_m = std::move(generateAgentFunc);
    propertyFactories_m = std::move(propertyFactories);
    eventFactories_m = std::move(eventFactories);
}

std::unique_ptr<Agent> AgentGenerator::generateAgent() {
    return generateAgentFunc_m(propertyFactories_m, eventFactories_m);
}
