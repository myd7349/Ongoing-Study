cmake_minimum_required(VERSION 3.14)

project(gcc7_3_1_build_error CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

add_executable(gcc7_3_1_build_error gcc7_3_1_build_error.cpp)
