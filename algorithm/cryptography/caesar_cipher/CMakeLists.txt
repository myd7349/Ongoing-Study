cmake_minimum_required(VERSION 3.8)

project(caesar_cipher C)

add_library(caesar_cipher caesar_cipher.c)
target_include_directories(caesar_cipher PUBLIC "${CMAKE_CURRENT_LIST_DIR}")

add_executable(caesar_cipher_test main.c)
target_link_libraries(caesar_cipher_test PRIVATE caesar_cipher)
