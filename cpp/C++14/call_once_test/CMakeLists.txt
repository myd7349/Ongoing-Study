cmake_minimum_required(VERSION 3.8)

project(call_once_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(call_once_test call_once_test.cpp)
add_executable(my_call_once_test my_call_once_test.cpp)


# References:
# https://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake
