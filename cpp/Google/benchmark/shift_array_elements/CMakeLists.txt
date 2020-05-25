cmake_minimum_required(VERSION 3.8)

project(shift_array_elements CXX)

find_package(benchmark CONFIG REQUIRED)

add_executable(shift_array_elements shift_array_elements.cpp)

target_link_libraries(
    shift_array_elements
    PRIVATE
        benchmark::benchmark
        #benchmark::benchmark_main
)
