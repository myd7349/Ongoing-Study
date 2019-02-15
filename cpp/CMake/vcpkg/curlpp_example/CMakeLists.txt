cmake_minimum_required(VERSION 3.9)

project(example CXX)

find_package(unofficial-curlpp CONFIG REQUIRED)

file(DOWNLOAD
    "https://raw.githubusercontent.com/jpbarrette/curlpp/master/examples/example00.cpp"
    "${CMAKE_SOURCE_DIR}/example00.cpp")

add_executable(example00 "example00.cpp")
target_link_libraries(example00 PRIVATE PRIVATE unofficial::curlpp::curlpp)
