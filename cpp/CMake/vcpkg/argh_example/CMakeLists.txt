cmake_minimum_required(VERSION 3.9)

project(argh_example)

find_package(argh CONFIG REQUIRED)

file(DOWNLOAD
    "https://raw.githubusercontent.com/adishavit/argh/master/example.cpp"
    "${CMAKE_SOURCE_DIR}/example.cpp")

add_executable(example "example.cpp")

target_link_libraries(example PRIVATE argh)
