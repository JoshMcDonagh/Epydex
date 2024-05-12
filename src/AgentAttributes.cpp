//
// Created by jmmar on 12/05/2024.
//

#include "../include/AgentAttributes.h"


AgentAttributes::AgentAttributes(Agents const agents) {
    agents_m = agents;
    propertyCount_m = 0;
    eventCount_m = 0;
}

void AgentAttributes::addProperty(Property& property) {
    properties_m.push_back(property);
    propertyIndexes_m[property.getName()] = propertyCount_m;
    propertyCount_m += 1;
}

void AgentAttributes::addEvent(Event& event) {
    events_m.push_back(event);
    eventIndexes_m[event.getName()] = eventCount_m;
    eventCount_m += 1;
}

Property AgentAttributes::getPropertyByIndex(int const index) {
    return properties_m[index];
}

Event AgentAttributes::getEventByIndex(int const index) {
    return events_m[index];
}

Property AgentAttributes::getPropertyByName(const std::string& name) {
    return properties_m[propertyIndexes_m[name]];
}

Event AgentAttributes::getEventByName(const std::string& name) {
    return events_m[eventIndexes_m[name]];
}




