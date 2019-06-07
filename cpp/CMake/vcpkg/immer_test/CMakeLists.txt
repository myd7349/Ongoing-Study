cmake_minimum_required(VERSION 3.12)

project(immer_test LANGUAGES CXX)

find_package(Immer CONFIG REQUIRED)
add_executable(vector_test vector_test.cpp)
target_link_libraries(vector_test PRIVATE immer)
