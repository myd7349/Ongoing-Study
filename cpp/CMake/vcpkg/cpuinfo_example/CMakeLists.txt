cmake_minimum_required(VERSION 3.8)

project(cpuinfo_example C)

find_package(cpuinfo CONFIG REQUIRED)

add_executable(example example.c)
target_link_libraries(example PRIVATE cpuinfo::clog cpuinfo::cpuinfo)
