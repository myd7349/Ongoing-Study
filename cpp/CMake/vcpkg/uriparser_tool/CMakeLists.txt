cmake_minimum_required(VERSION 3.8)

project(uriparse C)

find_package(uriparser CONFIG REQUIRED)

file(DOWNLOAD
    https://raw.githubusercontent.com/uriparser/uriparser/master/tool/uriparse.c
    ${CMAKE_BINARY_DIR}/uriparse.c
)

add_executable(uriparse ${CMAKE_BINARY_DIR}/uriparse.c)
target_link_libraries(uriparse PRIVATE uriparser::uriparser)
if (WIN32)
    target_link_libraries(uriparse PRIVATE Ws2_32)
endif ()
