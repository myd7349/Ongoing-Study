cmake_minimum_required(VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

project(is_unique_benchmark LANGUAGES CXX)

find_package(benchmark CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(is_unique_benchmark "is_unique_benchmark.cpp")

target_link_libraries(is_unique_benchmark PRIVATE benchmark::benchmark benchmark::benchmark_main)
