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
    explicit Event(std::string name, bool isRecorded,
                   std::function<bool(Agent&, Agents&)> triggerFunction,
                   std::function<void(Agent&, Agents&)> updateFunction);
    std::string getName();
    [[nodiscard]] bool isRecorded() const;
    [[nodiscard]] bool isTriggered() const;
    void runTick(Agent& agent, Agents& agents);

private:
    std::string name_m;
    bool isRecorded_m;
    bool isTriggered_m;
    std::function<bool(Agent&, Agents&)> triggerFunction_m;
    std::function<void(Agent&, Agents&)> updateFunction_m;
};



#endif //EVENT_H
