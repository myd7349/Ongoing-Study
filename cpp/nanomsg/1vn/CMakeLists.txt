cmake_minimum_required(VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake")
endif()

project(1vn CXX)

find_package(nanomsg CONFIG REQUIRED)

add_executable(client "client.cpp")
add_executable(server "server.cpp")

target_link_libraries(client PRIVATE nanomsg)
target_link_libraries(server PRIVATE nanomsg)

add_definitions(-D_CRT_SECURE_NO_WARNINGS=1 -D_CRT_NONSTDC_NO_DEPRECATE=1)
