//
// Created by Joshua McDonagh on 29/05/2024.
//

#ifndef AGENTGENERATOR_H
#define AGENTGENERATOR_H

#include <functional>
#include <vector>
#include <variant>
#include <memory>
#include <string>

#include "Agent.h"
#include "Property.h"
#include "Event.h"

using GenerateAgentFunc = std::function<std::unique_ptr<Agent>(std::vector<std::function<std::unique_ptr<Property<std::variant<int, double, std::string, bool>>>()>>,
                                                               std::vector<std::function<std::unique_ptr<Event>()>>)>;
using PropertyFactories = std::vector<std::function<std::unique_ptr<Property<std::variant<int, double, std::string, bool>>>()>>;
using EventFactories = std::vector<std::function<std::unique_ptr<Event>()>>;

class AgentGenerator {
public:
    AgentGenerator(GenerateAgentFunc generateAgentFunc,
                   PropertyFactories propertyFactories,
                   EventFactories eventFactories);
    std::unique_ptr<Agent> generateAgent();

private:
    GenerateAgentFunc generateAgentFunc_m;
    PropertyFactories propertyFactories_m;
    EventFactories eventFactories_m;
};

#endif // AGENTGENERATOR_H
