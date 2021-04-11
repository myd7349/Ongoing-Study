cmake_minimum_required(VERSION 3.8)

project(yyjson-test LANGUAGES C)

find_package(yyjson CONFIG REQUIRED)

add_executable(yyjson-test yyjson-test.c)
target_link_libraries(yyjson-test PRIVATE yyjson::yyjson)
