//
// Created by Joshua McDonagh on 29/05/2024.
//

#include "../include/AgentGenerator.h"

AgentGenerator::AgentGenerator(function<unique_ptr<Agent>(vector<function<unique_ptr<Property<variant<int, double, string, bool>>()>>>, vector<function<unique_ptr<Event>()>>)> generateAgentFunc,
                               vector<function<unique_ptr<Property<variant<int, double, string, bool>>()>>> propertyFactories,
                               vector<function<unique_ptr<Event>()>> eventFactories) {
    generateAgentFunc_m = std::move(generateAgentFunc);
    propertyFactories_m = std::move(propertyFactories);
    eventFactories_m = std::move(eventFactories);
}

unique_ptr<Agent> AgentGenerator::generateAgent() {
    return generateAgentFunc_m(propertyFactories_m, eventFactories_m);
}
