cmake_minimum_required(VERSION 3.8)

project(solve_demo C)

find_package(clapack CONFIG REQUIRED)

add_executable(solve_demo solve_demo.c)
target_link_libraries(solve_demo PRIVATE f2c lapack)
