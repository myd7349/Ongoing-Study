cmake_minimum_required(VERSION 3.8)

project(gcc-extensions C)

if (NOT CMAKE_C_COMPILER_ID STREQUAL "GNU")
    message(FATAL_ERROR "Your compiler is: ${CMAKE_C_COMPILER_ID}. GNU C is required.")
endif ()

set(test_sources
    statements_expression.c
)

foreach (test_src ${test_sources})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})
endforeach ()


# References:
# https://stackoverflow.com/questions/10046114/in-cmake-how-can-i-test-if-the-compiler-is-clang
