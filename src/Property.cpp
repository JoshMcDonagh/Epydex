//
// Created by jmmar on 12/05/2024.
//

#include <utility>

#include "../include/Property.h"

Property::Property(std::string name) {
    name_m = std::move(name);
}

std::string Property::getName() {
    return name_m;
}

