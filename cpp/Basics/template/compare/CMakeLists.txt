cmake_minimum_required(VERSION 3.8)

project(compare-example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(compare_example "compare_example.cpp")
