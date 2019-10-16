cmake_minimum_required(VERSION 3.8)
project(Graph CXX)
include(ExternalProject)

# include files
include_directories(./include ./src)


################################
# GTest
################################

ADD_SUBDIRECTORY(lemon-1.3.1)
list(SORT _variableNames)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach ()
include_directories(${CMAKE_BINARY_DIR}/lemon-1.3.1 ${LEMON_SOURCE_DIR})

################################
# Unit Tests
################################
# Add test cpp file
add_executable(Graph ./src/main.cpp)

# Link test executable against gtest & gtest_main
target_link_libraries(Graph PRIVATE lemon)