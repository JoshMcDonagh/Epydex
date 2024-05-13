//
// Created by jmmar on 12/05/2024.
//

#include <utility>

#include "../include/Property.h"

template<typename T>
Property<T>::Property(std::string name, T startingValue,
        std::function<T(T, Agent&, Agents&)> updateFunction) {
    name_m = std::move(name);
    value_m = std::move(startingValue);
    updateFunction_m = std::move(updateFunction);
}

template<typename T>
std::string Property<T>::getName() {
    return name_m;
}

template<typename T>
const std::type_info& Property<T>::getType() const {
    return typeid(value_m);
}

template<typename T>
void Property<T>::runTick(Agent& agent, Agents& agents) {
    value_m = updateFunction_m(value_m, agent, agents);
}

