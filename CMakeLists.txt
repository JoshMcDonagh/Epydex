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
        src/Event.cpp
        src/Agent.cpp
        src/AgentResults.cpp
        src/MemoryMappedTable.cpp
        src/AgentGenerator.cpp
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
        include/DataVariant.h
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
        include/DataVariant.h
)

# Download and integrate Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.11.0.zip
)
# Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add this section to create a test executable
add_executable(
        runTests
        tests/test_main.cpp
        tests/ClockTest.cpp  # Add your test files here
        src/model.cpp
        src/clock.cpp
        src/agents.cpp
        src/AgentAttributes.cpp
        src/Event.cpp
        src/Agent.cpp
        src/AgentResults.cpp
        src/MemoryMappedTable.cpp
        src/AgentGenerator.cpp
)

target_link_libraries(
        runTests
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(runTests)
