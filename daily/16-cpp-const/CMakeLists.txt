cmake_minimum_required(VERSION 4.2)
project(example_const LANGUAGES CXX)

set(PROJECT_CXX_STANDARD 23 CACHE STRING "C++ standard to use")
set_property(
        CACHE PROJECT_CXX_STANDARD
        PROPERTY STRINGS 11 14 17 20 23 26
)

add_executable(example_const const.cpp)
add_executable(example_mutable mutable.cpp)

set_target_properties(example_const PROPERTIES
        CXX_STANDARD "${PROJECT_CXX_STANDARD}"
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

message(STATUS "Building with C++${PROJECT_CXX_STANDARD}")