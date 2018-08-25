cmake_minimum_required(VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake")
endif()

project(nngbench C)

find_package(nng CONFIG REQUIRED)

add_executable(nngbench_client
    "nngbench_client.c"
    "../../high_timer.c"
    )
add_executable(nngbench_server
    "nngbench_server.c"
    "../../high_timer.c"
    )

target_link_libraries(nngbench_server PRIVATE nng::nng)
target_link_libraries(nngbench_client PRIVATE nng::nng)

add_definitions(-D_CRT_SECURE_NO_WARNINGS=1 -D_CRT_NONSTDC_NO_DEPRECATE=1)

# References:
# https://stackoverflow.com/questions/34937671/cmake-how-to-check-if-preprocessor-is-defined
