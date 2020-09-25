cmake_minimum_required(VERSION 3.8)

project(tinyexpr-test C)

find_package(unofficial-tinyexpr CONFIG REQUIRED)

add_executable(tinyexpr-test tinyexpr-test.c)
target_link_libraries(tinyexpr-test PRIVATE unofficial::tinyexpr::tinyexpr)
