cmake_minimum_required(VERSION 3.8)

project(RingBufferBenchmark CXX)

find_package(benchmark CONFIG REQUIRED)
find_package(boost REQUIRED)

add_executable(RingBufferBenchmark "RingBufferBenchmark.cpp")

target_link_libraries(RingBufferBenchmark PRIVATE benchmark::benchmark benchmark::benchmark_main)
