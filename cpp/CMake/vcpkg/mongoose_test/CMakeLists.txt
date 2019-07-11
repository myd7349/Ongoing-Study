cmake_minimum_required(VERSION 3.8)

project(mongoose-examples C)

find_package(unofficial-mongoose CONFIG REQUIRED)

file(DOWNLOAD
    "https://raw.githubusercontent.com/cesanta/mongoose/master/examples/tcp_echo_server/echo_server.c"
    "${CMAKE_CURRENT_BINARY_DIR}/echo_server.c")

add_executable(echo_server ${CMAKE_CURRENT_BINARY_DIR}/echo_server.c)
target_link_libraries(echo_server PRIVATE unofficial::mongoose::mongoose)
