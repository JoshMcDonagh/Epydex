//
// Created by jmmar on 12/05/2024.
//

#include <utility>

#include "../include/Event.h"

Event::Event(std::string name) {
    name_m = std::move(name);
}

std::string Event::getName() {
    return name_m;
}

