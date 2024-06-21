//
// Created by Joshua McDonagh on 12/05/2024.
//

#ifndef AGENTATTRIBUTES_H
#define AGENTATTRIBUTES_H

#include <map>
#include <vector>
#include <string>
#include "Property.h"
#include "DataVariant.h"
#include "Event.h"

// Forward declarations to avoid circular dependencies
class Agent;
class Agents;

class AgentAttributes {
public:
    explicit AgentAttributes(const Agents &agents);
    void addProperty(Property<DataVariant>& property);
    void addEvent(Event& event);
    std::vector<Property<DataVariant>> getProperties();
    std::vector<Event> getEvents();
    Property<DataVariant> getPropertyByIndex(int index);
    Event getEventByIndex(int index);
    Property<DataVariant> getPropertyByName(const std::string& name);
    Event getEventByName(const std::string& name);
    [[nodiscard]] int getNumOfProperties() const;
    [[nodiscard]] int getNumOfEvents() const;
    void runTick(const Agent* agent, const Agents* agents);
    std::map<std::string, int> getPropertyIndexes();
    std::map<std::string, int> getEventIndexes();

private:
    int propertyCount_m;
    int eventCount_m;
    std::vector<Property<DataVariant>> properties_m;
    std::vector<Event> events_m;
    std::map<std::string, int> propertyIndexes_m;
    std::map<std::string, int> eventIndexes_m;
};

#endif //AGENTATTRIBUTES_H
