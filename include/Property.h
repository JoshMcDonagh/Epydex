//
// Created by jmmar on 12/05/2024.
//

#ifndef PROPERTY_H
#define PROPERTY_H
#include <functional>
#include <optional>
#include <string>
#include <variant>

#include "Agents.h"


template<typename T>
class Property {
public:
    explicit Property(std::string name, T startingValue,
        std::function<T(T, Agent&, Agents&)> updateFunction);
    std::string getName();
    [[nodiscard]] const std::type_info& getType() const;
    void runTick(Agent& agent, Agents& agents);

private:
    std::string name_m;
    std::variant<int, double, std::string, bool> value_m;
    std::function<T(T, Agent&, Agents&)> updateFunction_m;
};



#endif //PROPERTY_H
