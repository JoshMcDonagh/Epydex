//
// Created by Joshua McDonagh on 22/05/2024.
//


#include "../include/AgentResults.h"

AgentResults::AgentResults(const std::string &agentName, const AgentAttributes& agentPhysiology,
                           const AgentAttributes& agentBehaviour)
        : agentPhysiology_m(agentPhysiology), agentBehaviour_m(agentBehaviour) {
    physiologyPropertyResultsFilename_m = agentName + "_" + physiologyPropertyResultsFilenameSuffix_m;
    behaviourPropertyResultsFilename_m = agentName + "_" + behaviourPropertyResultsFilenameSuffix_m;

    physiologyEventResultsFilename_m = agentName + "_" + physiologyEventResultsFilenameSuffix_m;
    behaviourEventResultsFilename_m = agentName + "_" + behaviourEventResultsFilenameSuffix_m;

    physiologyPropertyData_m = new MemoryMappedTable(physiologyPropertyResultsFilename_m, 0, agentPhysiology.getNumOfProperties());
    behaviourPropertyData_m = new MemoryMappedTable(behaviourPropertyResultsFilename_m, 0, agentBehaviour.getNumOfProperties());

    physiologyEventData_m = new MemoryMappedTable(physiologyEventResultsFilename_m, 0, agentPhysiology.getNumOfEvents());
    behaviourEventData_m = new MemoryMappedTable(behaviourEventResultsFilename_m, 0, agentBehaviour.getNumOfEvents());

    setPropertyHeaders(physiologyPropertyData_m, agentPhysiology_m.getProperties());
    setPropertyHeaders(behaviourPropertyData_m, agentBehaviour_m.getProperties());

    setEventHeaders(physiologyEventData_m, agentPhysiology_m.getEvents());
    setEventHeaders(behaviourEventData_m, agentBehaviour_m.getEvents());
}

AgentResults::~AgentResults() {
    free(physiologyPropertyData_m);
    free(behaviourPropertyData_m);
    free(physiologyEventData_m);
    free(behaviourEventData_m);
}

void AgentResults::runForProperties() {
    updateProperties(physiologyPropertyData_m, agentPhysiology_m.getProperties());
    updateProperties(behaviourPropertyData_m, agentBehaviour_m.getProperties());
}

void AgentResults::runForEvents() {
    updateEvents(physiologyEventData_m, agentPhysiology_m.getEvents());
    updateEvents(behaviourEventData_m, agentBehaviour_m.getEvents());
}

void AgentResults::setPropertyHeaders(MemoryMappedTable *storedData,
                                      const std::vector<Property<std::variant<int, double, std::string, bool>>> &properties) {
    std::vector<std::variant<int, double, std::string, bool>> propertyHeaders;
    for (auto property : properties) {
        if (property.isRecorded())
            propertyHeaders.emplace_back(property.getName());
    }
    storedData->addRow(propertyHeaders);
}

void AgentResults::setEventHeaders(MemoryMappedTable *storedData, const std::vector<Event> &events) {
    std::vector<std::variant<int, double, std::string, bool>> eventHeaders;
    for (auto event : events) {
        if (event.isRecorded())
            eventHeaders.emplace_back(event.getName());
    }
    storedData->addRow(eventHeaders);
}

void AgentResults::updateProperties(MemoryMappedTable *storedData, const std::vector<Property<std::variant<int, double, std::string, bool>>>& properties) {
    std::vector<std::variant<int, double, std::string, bool>> propertyData;
    for (auto property : properties) {
        if (property.isRecorded())
            propertyData.push_back(property.get());
    }
    storedData->addRow(propertyData);
}

void AgentResults::updateEvents(MemoryMappedTable *storedData, const std::vector<Event>& events) {
    std::vector<std::variant<int, double, std::string, bool>> eventData;
    for (const auto& event : events) {
        if (event.isRecorded())
            eventData.emplace_back(event.isTriggered());
    }
    storedData->addRow(eventData);
}
