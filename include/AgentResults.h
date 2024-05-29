//
// Created by Joshua McDonagh on 22/05/2024.
//

#ifndef AGENTRESULTS_H
#define AGENTRESULTS_H


#include <string>
#include "AgentAttributes.h"
#include "MemoryMappedTable.h"

class AgentResults {
public:
    AgentResults(const std::string &agentName, const AgentAttributes& agentPhysiology, const AgentAttributes& agentBehaviour);
    ~AgentResults();
    void runForProperties();
    void runForEvents();
private:
    static void setPropertyHeaders(MemoryMappedTable* storedData,
                                   const std::vector<Property<std::variant<int, double, std::string, bool>>>& properties);
    static void setEventHeaders(MemoryMappedTable* storedData, const std::vector<Event>& events);
    static void updateProperties(MemoryMappedTable* storedData,
                          const std::vector<Property<std::variant<int, double, std::string, bool>>>& properties);
    static void updateEvents(MemoryMappedTable* storedData, const std::vector<Event>& events);

    MemoryMappedTable* physiologyPropertyData_m;
    MemoryMappedTable* behaviourPropertyData_m;
    MemoryMappedTable* physiologyEventData_m;
    MemoryMappedTable* behaviourEventData_m;
    std::string physiologyPropertyResultsFilenameSuffix_m = "agent_physiology_property_results.dat";
    std::string behaviourPropertyResultsFilenameSuffix_m = "agent_behaviour_property_results.dat";
    std::string physiologyEventResultsFilenameSuffix_m = "agent_physiology_event_results.dat";
    std::string behaviourEventResultsFilenameSuffix_m = "agent_behaviour_event_results.dat";
    AgentAttributes agentPhysiology_m;
    AgentAttributes agentBehaviour_m;
    std::string physiologyPropertyResultsFilename_m;
    std::string behaviourPropertyResultsFilename_m;
    std::string physiologyEventResultsFilename_m;
    std::string behaviourEventResultsFilename_m;
};

#endif //AGENTRESULTS_H
