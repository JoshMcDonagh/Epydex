//
// Created by Joshua McDonagh on 12/05/2024.
//

#ifndef PROPERTY_H
#define PROPERTY_H

#include <functional>
#include <optional>
#include <string>
#include <variant>
#include <typeinfo>

#include "Agents.h"
#include "DataVariant.h"

class Agent;
class Agents;

template<typename T>
class Property {
public:
    explicit Property(std::string name, bool isRecorded, T startingValue,
                      std::function<T(T, const Agent*, const Agents*)> updateFunction);
    std::string getName();
    T get();
    [[nodiscard]] bool isRecorded() const;
    [[nodiscard]] const std::type_info& getType() const;
    void runTick(const Agent* agent, const Agents* agents);

private:
    std::string name_m;
    bool isRecorded_m;
    T value_m;
    std::function<T(T, const Agent*, const Agents*)> updateFunction_m;
};

template<typename T>
Property<T>::Property(std::string name, bool isRecorded, T startingValue,
                      std::function<T(T, const Agent*, const Agents*)> updateFunction)
        : name_m(std::move(name)), isRecorded_m(isRecorded), value_m(std::move(startingValue)), updateFunction_m(std::move(updateFunction)) {}

template<typename T>
std::string Property<T>::getName() {
    return name_m;
}

template<typename T>
T Property<T>::get() {
    return value_m;
}

template<typename T>
bool Property<T>::isRecorded() const {
    return isRecorded_m;
}

template<typename T>
const std::type_info& Property<T>::getType() const {
    return typeid(value_m);
}

template<typename T>
void Property<T>::runTick(const Agent* agent, const Agents* agents) {
    value_m = updateFunction_m(value_m, agent, agents);
}

// Explicit instantiation declaration (if needed)
extern template class Property<DataVariant>;

#endif // PROPERTY_H
