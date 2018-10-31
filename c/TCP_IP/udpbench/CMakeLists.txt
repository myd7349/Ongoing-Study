cmake_minimum_required(VERSION 3.8)

project(udpbench C)

if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS=1)
endif()

add_executable(udpbench_server
    "start_udp_server.c"
    "../get_in_addr.c"
    "../options.c"
    "../udpserver.c"
	"../../getprogname.c"
    "../../high_timer.c"
    "../../ttoi.c"
	"../../../algorithm/string/stringview.c"
	"../../../algorithm/string/substr.c"
    )

add_executable(udpbench_client
    "start_udp_client.c"
    "../get_in_addr.c"
    "../options.c"
    "../udpclient.c"
	"../../getprogname.c"
    "../../high_timer.c"
    "../../ttoi.c"
	"../../../algorithm/string/stringview.c"
	"../../../algorithm/string/substr.c"
    )

# Currently, find_package does work with `getopt-win32` when using vcpkg.
macro(import_getopt_win32 target_name)
    if(WIN32)
        target_include_directories(${target_name} PRIVATE "$ENV{VCPKG_ROOT}/installed/x86-windows/include")
        target_link_libraries(${target_name} PRIVATE "$ENV{VCPKG_ROOT}/installed/x86-windows/lib/getopt.lib")
        add_custom_command(TARGET ${target_name} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "$ENV{VCPKG_ROOT}/installed/x86-windows/bin/getopt.dll"
                $<TARGET_FILE_DIR:${target_name}>)
    endif()
endmacro()

import_getopt_win32(udpbench_server)
import_getopt_win32(udpbench_client)

# References:
# https://github.com/zeromq/libzmq/blob/master/CMakeLists.txt
