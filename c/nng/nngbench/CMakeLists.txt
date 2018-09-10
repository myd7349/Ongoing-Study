cmake_minimum_required(VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

project(nngbench C)

if(WIN32)
    if(MSVC)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS=1 -D_CRT_NONSTDC_NO_DEPRECATE=1)
    endif()

    add_definitions(-DUSING_UNICODE=0)
endif()

find_package(nng CONFIG REQUIRED)

option(USE_NNG_FLAG_ALLOC "Use NNG_FLAG_ALLOC flag" ON)

add_executable(nngbench_client
    "nngbench_client.c"
    "../../high_timer.c"
    "../../TCP_IP/ipv4.c"
    )
add_executable(nngbench_server
    "nngbench_server.c"
    "../../high_timer.c"
    )

target_link_libraries(nngbench_server PRIVATE nng::nng)
target_link_libraries(nngbench_client PRIVATE nng::nng)

if(USE_NNG_FLAG_ALLOC)
    add_definitions(-DUSE_NNG_FLAG_ALLOC=1)
endif()

# References:
# https://stackoverflow.com/questions/34937671/cmake-how-to-check-if-preprocessor-is-defined
