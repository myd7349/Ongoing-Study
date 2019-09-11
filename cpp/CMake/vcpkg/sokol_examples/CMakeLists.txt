cmake_minimum_required(VERSION 3.9)

project(sokol_examples C)

find_path(SOKOL_INCLUDE_DIR NAMES sokol_app.h)

add_executable(sokol_examples sokol_examples.c)
target_include_directories(sokol_examples PRIVATE ${SOKOL_INCLUDE_DIR})
