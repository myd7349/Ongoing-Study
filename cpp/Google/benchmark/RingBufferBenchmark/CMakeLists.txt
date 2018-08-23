cmake_minimum_required(VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake")
endif()

project(RingBufferBenchmark CXX)

find_package(benchmark CONFIG REQUIRED)
find_package(boost REQUIRED)

add_executable(RingBufferBenchmark "RingBufferBenchmark.cpp")

target_link_libraries(RingBufferBenchmark PRIVATE benchmark::benchmark benchmark::benchmark_main)
