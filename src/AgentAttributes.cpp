//
// Created by Joshua McDonagh on 12/05/2024.
//

#include "../include/AgentAttributes.h"


AgentAttributes::AgentAttributes(Agents const &agents) {
    propertyCount_m = 0;
    eventCount_m = 0;
}

void AgentAttributes::addProperty(Property<std::variant<int, double, std::string, bool>>& property) {
    properties_m.push_back(property);
    propertyIndexes_m[property.getName()] = propertyCount_m;
    propertyCount_m += 1;
}

void AgentAttributes::addEvent(Event& event) {
    events_m.push_back(event);
    eventIndexes_m[event.getName()] = eventCount_m;
    eventCount_m += 1;
}

Property<std::variant<int, double, std::string, bool>> AgentAttributes::getPropertyByIndex(int const index) {
    return properties_m[index];
}

Event AgentAttributes::getEventByIndex(int const index) {
    return events_m[index];
}

Property<std::variant<int, double, std::string, bool>> AgentAttributes::getPropertyByName(const std::string& name) {
    return properties_m[propertyIndexes_m[name]];
}

Event AgentAttributes::getEventByName(const std::string& name) {
    return events_m[eventIndexes_m[name]];
}

int AgentAttributes::getNumOfProperties() const {
    return propertyCount_m;
}

int AgentAttributes::getNumOfEvents() const {
    return eventCount_m;
}

void AgentAttributes::runTick(const Agent* agent, const Agents* agents) {
    // Run ticks for the stored properties
    for (int i = 0; i < propertyCount_m; i++)
        properties_m[i].runTick(agent, agents);

    // Run the ticks for the stored events
    for (int i = 0; i < eventCount_m; i++)
        events_m[i].runTick(agent, agents);
}

std::vector<Property<std::variant<int, double, std::string, bool>>> AgentAttributes::getProperties() {
    return properties_m;
}

std::vector<Event> AgentAttributes::getEvents() {
    return events_m;
}

std::map<std::string, int> AgentAttributes::getPropertyIndexes() {
    return propertyIndexes_m;
}

std::map<std::string, int> AgentAttributes::getEventIndexes() {
    return eventIndexes_m;
}
