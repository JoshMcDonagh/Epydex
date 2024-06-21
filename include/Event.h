//
// Created by Joshua McDonagh on 12/05/2024.
//

#ifndef EVENT_H
#define EVENT_H
#include <functional>
#include <string>
#include "Agents.h"

class Agent;
class Agents;

class Event {
public:
    explicit Event(std::string name, bool isRecorded,
                   std::function<bool(const Agent*, const Agents*)> triggerFunction,
                   std::function<void(const Agent*, const Agents*)> updateFunction);
    std::string getName() const;  // Note the 'const' keyword
    [[nodiscard]] bool isRecorded() const;
    [[nodiscard]] bool isTriggered() const;
    void runTick(const Agent* agent, const Agents* agents);

private:
    std::string name_m;
    bool isRecorded_m;
    bool isTriggered_m;
    std::function<bool(const Agent*, const Agents*)> triggerFunction_m;
    std::function<void(const Agent*, const Agents*)> updateFunction_m;
};

#endif //EVENT_H
