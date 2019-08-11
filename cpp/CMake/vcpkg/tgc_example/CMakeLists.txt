cmake_minimum_required(VERSION 3.9)

project(tgc_example C)

find_package(unofficial-tgc CONFIG REQUIRED)

add_executable(basic basic.c)
target_link_libraries(basic PRIVATE unofficial::tgc::tgc)
