cmake_minimum_required(VERSION 3.8)

project(regex_escape LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(regex_escape regex_escape.cpp)
target_include_directories(regex_escape PRIVATE "${CMAKE_CURRENT_LIST_DIR}/../../")
