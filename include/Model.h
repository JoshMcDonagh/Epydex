//
// Created by Joshua McDonagh on 09/05/2024.
//

#ifndef MODEL_H
#define MODEL_H

#include "Agents.h"
#include "Clock.h"

std::vector<AgentResults> run(int numOfCores, bool areTempFilesCleanedUp, Clock clock, Agents agents);

#endif //MODEL_H
