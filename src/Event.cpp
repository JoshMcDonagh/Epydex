//
// Created by jmmar on 12/05/2024.
//

#include <utility>

#include "../include/Event.h"

Event::Event(std::string name, std::function<bool(std::string, Agents&)> triggerFunction,
        std::function<void(std::string, Agents&)> updateFunction) {
    name_m = std::move(name);
    triggerFunction_m = std::move(triggerFunction);
    updateFunction_m = std::move(updateFunction);
}

std::string Event::getName() {
    return name_m;
}

std::function<bool(std::string, Agents &)> Event::getTriggerFunction() {
    return triggerFunction_m;
}

std::function<void(std::string, Agents &)> Event::getUpdateFunction() {
    return updateFunction_m;
}

