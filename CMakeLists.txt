cmake_minimum_required(VERSION 3.28)
project(Epydex)

set(CMAKE_CXX_STANDARD 26)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add library
add_library(Epydex SHARED
        src/model.cpp
        src/clock.cpp
        src/agents.cpp
        src/AgentAttributes.cpp
        src/Property.cpp
        src/Event.cpp
        src/Agent.cpp
        src/AgentResults.cpp
        src/MemoryMappedTable.cpp
        src/AgentGenerator.cpp
)

# List header files for clarity (not strictly necessary)
set(HEADERS
        include/model.h
        include/clock.h
        include/agents.h
        include/AgentAttributes.h
        include/Property.h
        include/Event.h
        include/Agent.h
        include/AgentResults.h
        include/MemoryMappedTable.h
        include/AgentGenerator.h
)