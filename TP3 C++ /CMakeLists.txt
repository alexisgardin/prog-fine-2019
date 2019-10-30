cmake_minimum_required(VERSION 3.8)
project(Graph CXX)
include(ExternalProject)
FIND_PACKAGE(Boost 1.7.0 COMPONENTS string_algo)
set(Boost_USE_STATIC_LIBS ON) # only find static libs
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(CMAKE_CXX_STANDARD 11)
# include files
include_directories(./include ./src)


################################
# GTest
################################

#ADD_SUBDIRECTORY(lemon-1.3.1)
list(SORT _variableNames)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach ()
#include_directories(${CMAKE_BINARY_DIR}/lemon-1.3.1 ${LEMON_SOURCE_DIR} ${Boost_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})

link_directories(${Boost_LIBRARY_DIR})
################################
# Unit Tests
################################
# Add test cpp file
add_executable(Graph ./src/main.cpp src/Algorithm/strategies/Algorithm.cpp src/Algorithm/strategies/Algorithm.h src/Algorithm/model/Edge.cpp src/Algorithm/model/Edge.h src/Algorithm/model/Graph.cpp src/Algorithm/model/Graph.h src/Algorithm/model/Node.cpp src/Algorithm/model/Node.h src/Algorithm/strategies/AlgorithmTabu.cpp src/Algorithm/strategies/AlgorithmTabu.h src/Algorithm/strategies/AlgorithmGreedy.cpp src/Algorithm/strategies/AlgorithmGreedy.h src/Algorithm/strategies/AlgorithmQuadra.cpp src/Algorithm/strategies/AlgorithmQuadra.h)

# Link test executable against gtest & gtest_main
target_link_libraries(Graph ${Boost_LIBRARIES})