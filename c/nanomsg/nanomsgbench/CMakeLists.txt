cmake_minimum_required(VERSION 3.8)

if(WIN32)
    if(MSVC)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS=1)
    endif()

    add_definitions(-DUSING_UNICODE=0)

    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

project(nanomsgbench C)

find_package(nanomsg CONFIG REQUIRED)

add_executable(nanomsgbench_client
    "nanomsgbench_client.c"
    "../../high_timer.c"
    "../../TCP_IP/ipv4.c"
    )
add_executable(nanomsgbench_server
    "nanomsgbench_server.c"
    "../../high_timer.c"
    )

target_link_libraries(nanomsgbench_client PRIVATE nanomsg)
target_link_libraries(nanomsgbench_server PRIVATE nanomsg)

add_definitions(-D_CRT_SECURE_NO_WARNINGS=1 -D_CRT_NONSTDC_NO_DEPRECATE=1)

# References:
# https://stackoverflow.com/questions/34937671/cmake-how-to-check-if-preprocessor-is-defined
