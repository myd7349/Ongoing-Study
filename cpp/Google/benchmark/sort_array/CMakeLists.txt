cmake_minimum_required(VERSION 3.8)

project(sort_array CXX)

find_package(benchmark CONFIG REQUIRED)

add_executable(sort_array sort_array.cpp)

target_link_libraries(
    sort_array
    PRIVATE
        benchmark::benchmark
        benchmark::benchmark_main
)
