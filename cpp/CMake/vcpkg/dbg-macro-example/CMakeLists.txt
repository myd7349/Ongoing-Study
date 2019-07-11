cmake_minimum_required(VERSION 3.8)

project(dbg-macro-example CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_path(
    DBG_MACRO_INCLUDE_DIR
    NAMES dbg.h
)

file(DOWNLOAD
    "https://raw.githubusercontent.com/sharkdp/dbg-macro/master/tests/example.cpp"
    "${CMAKE_CURRENT_BINARY_DIR}/example.cpp")

add_executable(dbg-macro-example ${CMAKE_CURRENT_BINARY_DIR}/example.cpp)
target_include_directories(dbg-macro-example PRIVATE ${DBG_MACRO_INCLUDE_DIR})
