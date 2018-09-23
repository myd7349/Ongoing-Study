cmake_minimum_required(VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake")
endif()

project(ConcurrentQueueBenchmark CXX)

find_package(benchmark CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS thread)

if(Boost_FOUND)
    add_definitions(-DHAS_BOOST)
	message("Boost libraries: ${Boost_system_LIBRARIES}")
endif()

add_executable(ConcurrentQueueBenchmark "ConcurrentQueueBenchmark.cpp")

target_include_directories(ConcurrentQueueBenchmark PRIVATE "$ENV{VCPKG_DIR}/installed/x86-windows/include")

target_link_libraries(ConcurrentQueueBenchmark PRIVATE benchmark::benchmark benchmark::benchmark_main)


# References:
# https://github.com/Microsoft/vcpkg/issues/4188
