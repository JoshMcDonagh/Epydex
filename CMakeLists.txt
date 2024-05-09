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
        include/ModelResults.h)
