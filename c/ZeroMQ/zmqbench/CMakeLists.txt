cmake_minimum_required(VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

project(zmqbench C)

find_package(ZeroMQ CONFIG REQUIRED)

add_executable(zmqbench_client
    "zmqbench_client.c"
    "../../high_timer.c"
    )
add_executable(zmqbench_server
    "zmqbench_server.c"
    "../../high_timer.c"
    )

add_definitions(-D_CRT_SECURE_NO_WARNINGS=1 -D_CRT_NONSTDC_NO_DEPRECATE=1)

target_link_libraries(zmqbench_client PRIVATE libzmq libzmq-static)
target_link_libraries(zmqbench_server PRIVATE libzmq libzmq-static)

# References:
# https://stackoverflow.com/questions/34937671/cmake-how-to-check-if-preprocessor-is-defined
