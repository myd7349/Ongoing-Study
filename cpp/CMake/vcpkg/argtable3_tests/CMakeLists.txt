cmake_minimum_required(VERSION 3.9)

project(argtable3_tests C)

find_package(Argtable3 CONFIG REQUIRED)

file(DOWNLOAD
    "https://raw.githubusercontent.com/argtable/argtable3/master/examples/echo.c"
    "${CMAKE_CURRENT_BINARY_DIR}/echo.c"
)

add_executable(echo "${CMAKE_CURRENT_BINARY_DIR}/echo.c")
target_link_libraries(echo PRIVATE argtable3 argtable3_static)
