cmake_minimum_required(VERSION 3.8)
project(call_once_test C)
set(CMAKE_C_STANDARD 11)
add_executable(call_once_test call_once_test.c)

# References:
# https://stackoverflow.com/questions/39960169/cmake-cmakelists-for-c11
