cmake_minimum_required(VERSION 3.10)

project(edflib-test C)

find_package(unofficial-EDFlib CONFIG REQUIRED)

if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/main.cpp")
    file(DOWNLOAD
        "https://gitlab.com/Teuniz/EDFlib/-/raw/master/sweep_generator.c"
        "${CMAKE_CURRENT_BINARY_DIR}/sweep_generator.c"
    )
endif()

add_executable(sweep_generator "${CMAKE_CURRENT_BINARY_DIR}/sweep_generator.c")
target_link_libraries(sweep_generator PRIVATE EDFlib)
