//
// Created by Joshua McDonagh on 12/05/2024.
//

#ifndef PROPERTY_H
#define PROPERTY_H
#include <functional>
#include <optional>
#include <string>
#include <variant>

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
    DataVariant value_m;
    std::function<T(T, Agent&, Agents&)> updateFunction_m;
};

extern template class Property<DataVariant>;

#endif //PROPERTY_H