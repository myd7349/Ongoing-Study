cmake_minimum_required(VERSION 3.9)

project(liboglcommon C CXX)

find_package(glew CONFIG REQUIRED)

add_library(
    liboglcommon
    shader.cpp
)

target_include_directories(
    liboglcommon
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)

target_link_libraries(
    liboglcommon
    PUBLIC
        GLEW::GLEW
)
