cmake_minimum_required(VERSION 3.28)
project(PyNex)

set(CMAKE_CXX_STANDARD 26)

add_library(PyNex SHARED
        include/model.h
        src/model.cpp
        src/clock.cpp
        include/clock.h
        src/agents.cpp
        include/agents.h
        src/ModelResults.cpp
        include/ModelResults.h
        src/AgentAttributes.cpp
        include/AgentAttributes.h
        src/Property.cpp
        include/Property.h
        src/Event.cpp
        include/Event.h
        src/Agent.cpp
        include/Agent.h
        src/AgentResults.cpp
        include/AgentResults.h
        src/MemoryMappedTable.cpp
        include/MemoryMappedTable.h)
