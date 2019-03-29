cmake_minimum_required(VERSION 3.10)

project(normal_distribution LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(normal_distribution "normal_distribution.cpp")
