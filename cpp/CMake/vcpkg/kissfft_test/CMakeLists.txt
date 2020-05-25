cmake_minimum_required(VERSION 3.9)

project(kissfft_test C CXX)

find_package(unofficial-kissfft CONFIG REQUIRED)

add_executable(kissfft_test kissfft_test.cpp)
target_link_libraries(kissfft_test PRIVATE unofficial::kissfft::kissfft)
