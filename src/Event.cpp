//
// Created by Joshua McDonagh on 12/05/2024.
//

#include <utility>
#include "../include/Event.h"

Event::Event(std::string name, bool isRecorded,
             std::function<bool(const Agent*, const Agents*)> triggerFunction,
             std::function<void(const Agent*, const Agents*)> updateFunction)
    : name_m(std::move(name)), isRecorded_m(isRecorded), isTriggered_m(false),
      triggerFunction_m(std::move(triggerFunction)), updateFunction_m(std::move(updateFunction)) {}

std::string Event::getName() const {  // Added const
    return name_m;
}

bool Event::isRecorded() const {
    return isRecorded_m;
}

bool Event::isTriggered() const {
    return isTriggered_m;
}

void Event::runTick(const Agent* agent, const Agents* agents) {
    if (triggerFunction_m(agent, agents)) {
        isTriggered_m = true;
        updateFunction_m(agent, agents);
    } else {
        isTriggered_m = false;
    }
}
