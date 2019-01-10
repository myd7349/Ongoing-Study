cmake_minimum_required(VERSION 3.8)

project(put_time_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(put_time_test "put_time_test.cpp")

# References:
# https://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake
