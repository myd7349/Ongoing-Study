cmake_minimum_required(VERSION 3.8)

project(enum-demo LANGUAGES CXX)

find_package(hdf5 CONFIG REQUIRED)

add_executable(enum-demo enum-demo.cpp)
target_link_libraries(enum-demo PRIVATE hdf5::hdf5_cpp-shared)
target_compile_features(enum-demo PRIVATE cxx_std_11)
