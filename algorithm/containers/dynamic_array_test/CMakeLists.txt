cmake_minimum_required (VERSION 3.8)
project(dynamic_array_test C)
add_library(dynamic_array "${CMAKE_CURRENT_LIST_DIR}/../dynamic_array.c")
target_include_directories(dynamic_array PUBLIC "${CMAKE_CURRENT_LIST_DIR}/..")
add_executable(dynamic_array_test dynamic_array_test.c)
target_link_libraries(dynamic_array_test PRIVATE dynamic_array)

# References:
# https://github.com/Microsoft/vcpkg/issues/1094
# https://github.com/Microsoft/vcpkg/blob/8379a80abe5288c7c06d5b9ab16efe355d1c6f62/docs/EXAMPLES.md#example-1-2-b