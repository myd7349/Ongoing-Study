cmake_minimum_required(VERSION 3.8)
project(xassert_test LANGUAGES C)
add_executable(xassert_test xassert_test.c ${CMAKE_CURRENT_LIST_DIR}/../xassert.c)
