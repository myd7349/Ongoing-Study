cmake_minimum_required(VERSION 3.8)

project(conv_test C)

add_executable(conv_test
    ../../algutils.c
    ../mathutils.c
    conv_test.c
)
