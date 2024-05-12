//
// Created by jmmar on 12/05/2024.
//

#include <utility>

#include "../include/Property.h"

template<typename T>
Property<T>::Property(std::string name, T startingValue,
        std::function<void(std::string, T, Agents&)> updateFunction) {
    name_m = std::move(name);
    startingValue_m = std::move(startingValue);
    updateFunction_m = std::move(updateFunction);
}

template<typename T>
std::string Property<T>::getName() {
    return name_m;
}

template<typename T>
T Property<T>::getStartingValue() {
    return startingValue_m;
}

template<typename T>
std::function<void(std::string, T, Agents &)> Property<T>::getUpdateFunction() {
    return updateFunction_m;
}

