cmake_minimum_required(VERSION 3.8)

project(tcpchatroomserv C)

if(WIN32)
    if(MSVC)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS=1 -D_CRT_NONSTDC_NO_DEPRECATE=1)
    endif()

    add_definitions(-DUSING_UNICODE=0)
endif()

set(SRCS
    "start_select_server.c"
    "../tcpsrv.c"
    "../get_in_addr.c"
    "../sendall.c"
    "../tcpopt.c"
    "../../ttoi.c"
    )

add_executable(tcpchatroomserv ${SRCS})
