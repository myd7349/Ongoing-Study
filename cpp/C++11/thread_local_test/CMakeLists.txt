cmake_minimum_required(VERSION 3.8)

project(thread_local_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(thread_local_test "thread_local_test.cpp")
