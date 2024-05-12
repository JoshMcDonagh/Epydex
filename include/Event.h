//
// Created by jmmar on 12/05/2024.
//

#ifndef EVENT_H
#define EVENT_H
#include <functional>
#include <string>

#include "Agents.h"


class Event {
public:
    explicit Event(std::string name, std::function<bool(std::string, Agents&)> triggerFunction,
        std::function<void(std::string, Agents&)> updateFunction);
    std::string getName();
    std::function<bool(std::string, Agents&)> getTriggerFunction();
    std::function<void(std::string, Agents&)> getUpdateFunction();

private:
    std::string name_m;
    std::function<bool(std::string, Agents&)> triggerFunction_m;
    std::function<void(std::string, Agents&)> updateFunction_m;
};



#endif //EVENT_H
