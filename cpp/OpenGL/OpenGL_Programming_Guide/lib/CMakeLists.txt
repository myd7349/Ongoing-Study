cmake_minimum_required(VERSION 3.9)

project(libredbook C CXX)

find_package(gl3w CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_library(
    libredbook
    LoadShaders.cpp
    vermilion.cpp
)

target_include_directories(
    libredbook
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)

target_link_libraries(
    libredbook
    PUBLIC
        glfw
        unofficial::gl3w::gl3w
)
