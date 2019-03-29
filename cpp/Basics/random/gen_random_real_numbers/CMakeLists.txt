cmake_minimum_required(VERSION 3.10)

project(gen_random_real_numbers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(gen_random_real_numbers "gen_random_real_numbers.cpp")
