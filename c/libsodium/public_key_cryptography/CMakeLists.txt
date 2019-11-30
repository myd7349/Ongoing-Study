cmake_minimum_required(VERSION 3.8)

project(public_key_cryptography C)

find_package(unofficial-sodium CONFIG REQUIRED)

add_executable(public_key_cryptography public_key_cryptography.c)
target_link_libraries(public_key_cryptography PRIVATE unofficial-sodium::sodium)
