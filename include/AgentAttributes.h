//
// Created by Joshua McDonagh on 12/05/2024.
//

#ifndef AGENTATTRIBUTES_H
#define AGENTATTRIBUTES_H
#include <map>
#include <vector>

#include "Agents.h"
#include "Property.h"
#include "Event.h"


class Agent;
class Agents;


class AgentAttributes {
public:
    explicit AgentAttributes(const Agents &agents);
    void addProperty(Property<std::variant<int, double, std::string, bool>>& property);
    void addEvent(Event& event);
    std::vector<Property<std::variant<int, double, std::string, bool>>> getProperties();
    std::vector<Event> getEvents();
    Property<std::variant<int, double, std::string, bool>> getPropertyByIndex(int index);
    Event getEventByIndex(int index);
    Property<std::variant<int, double, std::string, bool>> getPropertyByName(const std::string& name);
    Event getEventByName(const std::string& name);
    [[nodiscard]] int getNumOfProperties() const;
    [[nodiscard]] int getNumOfEvents() const;
    void runTick(const Agent* agent, const Agents* agents);

private:
    int propertyCount_m;
    int eventCount_m;
    std::vector<Property<std::variant<int, double, std::string, bool>>> properties_m;
    std::vector<Event> events_m;
    std::map<std::string, int> propertyIndexes_m;
    std::map<std::string, int> eventIndexes_m;
};



#endif //AGENTATTRIBUTES_H
