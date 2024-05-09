//
// Created by jmmar on 09/05/2024.
//

#ifndef MODEL_H
#define MODEL_H

#include "Agents.h"
#include "Clock.h"
#include "ModelResults.h"

ModelResults run(
    int numOfAgents,
    Clock clock,
    Agents agents,
    ModelResults results);

#endif //MODEL_H
