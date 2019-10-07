cmake_minimum_required(VERSION 3.9)

project(mathc_test C)

find_package(unofficial-mathc CONFIG REQUIRED)

add_executable(mathc_test mathc_test.c)
target_link_libraries(mathc_test PRIVATE unofficial::mathc::mathc)
