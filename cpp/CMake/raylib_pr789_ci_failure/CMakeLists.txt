cmake_minimum_required(VERSION 3.0)

project(ralib C)

option(REPRODUCE_CI_BUILD_ERROR "Build the examples." ON)
option(BUILD_EXAMPLES "Build the examples." ON)

add_subdirectory(src)

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# References:
# https://github.com/raysan5/raylib/pull/789
# https://github.com/raysan5/raylib/pull/789#issuecomment-482923913
