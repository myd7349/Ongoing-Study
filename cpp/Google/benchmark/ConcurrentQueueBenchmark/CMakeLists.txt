cmake_minimum_required(VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake")
endif()

project(ConcurrentQueueBenchmark CXX)

find_package(benchmark CONFIG REQUIRED)

add_executable(ConcurrentQueueBenchmark "ConcurrentQueueBenchmark.cpp")

target_include_directories(ConcurrentQueueBenchmark PRIVATE "$ENV{VCPKG_DIR}/installed/x86-windows/include")

target_link_libraries(ConcurrentQueueBenchmark PRIVATE benchmark::benchmark benchmark::benchmark_main)
