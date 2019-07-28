cmake_minimum_required(VERSION 3.9)

project(cello_example C)

find_package(unofficial-cello CONFIG REQUIRED)

add_executable(cello_world cello_world.c)
target_link_libraries(cello_world PRIVATE unofficial::cello::cello)
