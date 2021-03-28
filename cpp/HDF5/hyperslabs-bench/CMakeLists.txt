cmake_minimum_required(VERSION 3.8)

project(hyperslabs-bench LANGUAGES CXX)

find_package(CLI11 CONFIG REQUIRED)
find_package(hdf5 CONFIG REQUIRED)

macro(create_bench target sources)
    add_executable(${target} ${sources})
    target_include_directories(${target} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/../../C++11")
    target_link_libraries(${target} PRIVATE CLI11::CLI11 hdf5::hdf5_cpp-shared)
    target_compile_features(${target} PRIVATE cxx_std_11)
endmacro()

create_bench(hyperslabs-write-bench hyperslabs-write-bench.cpp)
create_bench(hyperslabs-read-bench hyperslabs-read-bench.cpp)

# References:
# [How do I activate C++ 11 in CMake?](https://stackoverflow.com/questions/10851247/how-do-i-activate-c-11-in-cmake)
# [Take control of your vcpkg dependencies with versioning support](https://devblogs.microsoft.com/cppblog/take-control-of-your-vcpkg-dependencies-with-versioning-support/)
