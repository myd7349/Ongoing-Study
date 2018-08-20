cmake_minimum_required(VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake")
endif()

project(ConcurrentVectorBenchmark CXX)

find_package(benchmark CONFIG REQUIRED)

add_executable(ConcurrentVectorBenchmark "ConcurrentVectorBenchmark.cpp")

target_link_libraries(ConcurrentVectorBenchmark PRIVATE benchmark::benchmark benchmark::benchmark_main)
