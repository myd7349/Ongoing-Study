cmake_minimum_required(VERSION 3.8)

project(shared_ptr_use_count CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(shared_ptr_use_count "shared_ptr_use_count.cpp")
