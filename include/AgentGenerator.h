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

using namespace std;
using GenerateAgentFunc = function<unique_ptr<Agent>(vector<function<unique_ptr<Property<variant<int, double, string, bool>>>()>>,
                                 vector<function<unique_ptr<Event>()>>)>;
using PropertyFactories = vector<function<unique_ptr<Property<variant<int, double, string, bool>>>()>>;
using EventFactories = vector<function<unique_ptr<Event>()>>;

class AgentGenerator {
public:
    AgentGenerator(GenerateAgentFunc generateAgentFunc,
                   PropertyFactories propertyFactories,
                   EventFactories eventFactories);
    unique_ptr<Agent> generateAgent();

private:
    GenerateAgentFunc generateAgentFunc_m;
    PropertyFactories propertyFactories_m;
    EventFactories eventFactories_m;
};

#endif // AGENTGENERATOR_H
