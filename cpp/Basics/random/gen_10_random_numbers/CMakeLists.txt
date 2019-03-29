cmake_minimum_required(VERSION 3.10)

project(gen_10_random_numbers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(gen_10_random_numbers "gen_10_random_numbers.cpp")
