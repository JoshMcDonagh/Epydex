//
// Created by jmmar on 12/05/2024.
//

#ifndef AGENTATTRIBUTES_H
#define AGENTATTRIBUTES_H
#include <map>
#include <vector>

#include "Agents.h"
#include "Property.h"
#include "Event.h"


class AgentAttributes {
public:
    explicit AgentAttributes(Agents agents);
    void addProperty(Property& property);
    void addEvent(Event& event);
    Property getPropertyByIndex(int index);
    Event getEventByIndex(int index);
    Property getPropertyByName(const std::string& name);
    Event getEventByName(const std::string& name);
    [[nodiscard]] int getNumOfProperties() const;
    [[nodiscard]] int getNumOfEvents() const;

private:
    Agents agents_m;
    int propertyCount_m;
    int eventCount_m;
    std::vector<Property> properties_m;
    std::vector<Event> events_m;
    std::map<std::string, int> propertyIndexes_m;
    std::map<std::string, int> eventIndexes_m;
};



#endif //AGENTATTRIBUTES_H
