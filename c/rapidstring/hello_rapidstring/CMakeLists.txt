cmake_minimum_required(VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

project(hello_rapidstring C)

find_package(unofficial-rapidstring CONFIG REQUIRED)

add_executable(hello_rapidstring "hello_rapidstring.c")

target_link_libraries(hello_rapidstring PRIVATE unofficial::rapidstring::rapidstring)
