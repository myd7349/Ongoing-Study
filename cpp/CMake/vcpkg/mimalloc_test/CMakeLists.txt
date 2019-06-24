cmake_minimum_required(VERSION 3.8)

project(mimalloc-tests C)

find_package(mimalloc 1.0 REQUIRED)
file(DOWNLOAD
    "https://raw.githubusercontent.com/microsoft/mimalloc/master/test/main.c"
    "${CMAKE_CURRENT_BINARY_DIR}/main.c")
add_executable(main ${CMAKE_CURRENT_BINARY_DIR}/main.c)
if (TARGET mimalloc)
    target_link_libraries(main PRIVATE mimalloc)
elseif (TARGET mimalloc-static)
    target_link_libraries(main PRIVATE mimalloc-static)
endif ()
