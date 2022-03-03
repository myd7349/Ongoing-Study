cmake_minimum_required(VERSION 3.8)
project(setenv C)

add_executable(setenv setenv.c)
target_compile_definitions(setenv PRIVATE UNICODE _UNICODE)
