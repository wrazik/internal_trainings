cmake_minimum_required(VERSION 3.28)
project(44_buffer_overflow)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Boost REQUIRED COMPONENTS system)
find_package(Threads REQUIRED)

add_executable(44_buffer_overflow main.cpp)
target_link_libraries(44_buffer_overflow PRIVATE Boost::system Threads::Threads)

target_compile_options(44_buffer_overflow PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -fno-stack-protector
        -g
)

target_link_options(44_buffer_overflow PRIVATE
        -z execstack
        -no-pie
)