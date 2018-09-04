cmake_minimum_required(VERSION 3.8)

project(tcpechoclient C)

if(WIN32)
    if(MSVC)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS=1)
    endif()

    add_definitions(-DUSING_UNICODE=0)
endif()

add_executable(tcpechoclient
    "start_client.c"
    "../get_in_addr.c"
    "../options.c"
    "../tcpclient.c"
    "../../getprogname.c"
    "../../ttoi.c"
    "../../../algorithm/string/stringview.c"
    "../../../algorithm/string/substr.c"
    )

if(WIN32)
    target_include_directories(tcpechoclient PRIVATE "$ENV{VCPKG_ROOT}/installed/x86-windows/include")
    target_link_libraries(tcpechoclient PRIVATE "$ENV{VCPKG_ROOT}/installed/x86-windows/lib/getopt.lib")
    add_custom_command(TARGET tcpechoclient POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$ENV{VCPKG_ROOT}/installed/x86-windows/bin/getopt.dll"
            $<TARGET_FILE_DIR:tcpechoclient>)
endif()
