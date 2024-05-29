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

class AgentGenerator {
public:
    AgentGenerator(function<unique_ptr<Agent>(vector<function<unique_ptr<Property<variant<int, double, string, bool>>()>>>,vector<function<unique_ptr<Event>()>>)>,
                   vector<function<unique_ptr<Property<variant<int, double, string, bool>>()>>>,
                   vector<function<unique_ptr<Event>()>>);
    unique_ptr<Agent> generateAgent();

private:
    function<unique_ptr<Agent>(vector<function<unique_ptr<Property<variant<int, double, string, bool>>()>>>,
                    vector<function<unique_ptr<Event>()>>)> generateAgentFunc_m;
    vector<function<unique_ptr<Property<variant<int, double, string, bool>>()>>> propertyFactories_m;
    vector<function<unique_ptr<Event>()>> eventFactories_m;
};

#endif // AGENTGENERATOR_H
