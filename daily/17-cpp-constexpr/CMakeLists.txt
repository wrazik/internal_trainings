cmake_minimum_required(VERSION 4.2)
project(example_const LANGUAGES CXX)

set(PROJECT_CXX_STANDARD 23 CACHE STRING "C++ standard to use")
set_property(
        CACHE PROJECT_CXX_STANDARD
        PROPERTY STRINGS 11 14 17 20 23 26
)

function(add_cpp_example name)
    add_executable(${name} ${name}.cpp)

    set_target_properties(${name} PROPERTIES
            CXX_STANDARD "${PROJECT_CXX_STANDARD}"
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
    )
endfunction()

add_cpp_example(cpp11_1)
add_cpp_example(cpp11_2)
add_cpp_example(cpp11_3)
add_cpp_example(cpp14)
add_cpp_example(cpp17_1)

message(STATUS "Building with C++${PROJECT_CXX_STANDARD}")