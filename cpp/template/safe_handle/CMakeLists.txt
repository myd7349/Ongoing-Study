cmake_minimum_required(VERSION 3.8)
project(safe_handle CXX)

add_executable(safe_handle_v1 safe_handle_v1.cpp)
target_compile_features(safe_handle_v1 PUBLIC cxx_std_11)

add_executable(safe_handle_v2 safe_handle_v2.cpp)
target_compile_features(safe_handle_v2 PUBLIC cxx_std_11)
