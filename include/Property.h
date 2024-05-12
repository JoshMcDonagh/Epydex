//
// Created by jmmar on 12/05/2024.
//

#ifndef PROPERTY_H
#define PROPERTY_H
#include <functional>
#include <string>
#include <variant>

#include "Agents.h"


template<typename T>
class Property {
public:
    explicit Property(std::string name, T startingValue,
        std::function<void(std::string, T, Agents&)> updateFunction);
    std::string getName();
    T getStartingValue();
    std::function<void(std::string, T, Agents&)> getUpdateFunction();
    [[nodiscard]] const std::type_info& getType() const;

private:
    std::string name_m;
    std::variant<int, double, std::string, bool> startingValue_m;
    std::function<void(std::string, T, Agents&)> updateFunction_m;
};



#endif //PROPERTY_H
