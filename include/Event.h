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
    explicit Event(std::string name, std::function<bool(Agent&, Agents&)> triggerFunction,
        std::function<void(Agent&, Agents&)> updateFunction);
    std::string getName();
    void runTick(Agent& agent, Agents& agents);

private:
    std::string name_m;
    std::function<bool(Agent&, Agents&)> triggerFunction_m;
    std::function<void(Agent&, Agents&)> updateFunction_m;
};



#endif //EVENT_H
