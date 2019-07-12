cmake_minimum_required(VERSION 3.8)

project(nameof-example CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(nameof CONFIG REQUIRED)

file(DOWNLOAD
    "https://raw.githubusercontent.com/Neargye/nameof/master/example/example.cpp"
    "${CMAKE_CURRENT_BINARY_DIR}/example.cpp")

add_executable(nameof-example ${CMAKE_CURRENT_BINARY_DIR}/example.cpp)
target_link_libraries(nameof-example PRIVATE nameof::nameof)
