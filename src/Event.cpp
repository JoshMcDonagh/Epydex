//
// Created by jmmar on 12/05/2024.
//

#include <utility>

#include "../include/Event.h"

Event::Event(std::string name, std::function<bool(Agent&, Agents&)> triggerFunction,
        std::function<void(Agent&, Agents&)> updateFunction) {
    name_m = std::move(name);
    triggerFunction_m = std::move(triggerFunction);
    updateFunction_m = std::move(updateFunction);
}

std::string Event::getName() {
    return name_m;
}

void Event::runTick(Agent &agent, Agents &agents) {
    if (triggerFunction_m(agent, agents)) {
        updateFunction_m(agent, agents);
    }
}
