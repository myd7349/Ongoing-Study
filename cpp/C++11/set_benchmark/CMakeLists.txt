cmake_minimum_required(VERSION 3.8)

project(set_benchmark LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(set_benchmark
    "set_benchmark.cpp"
    "../../Stopwatch.cpp")
