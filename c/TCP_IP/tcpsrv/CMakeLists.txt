cmake_minimum_required(VERSION 3.8)

project(tcpsrv C)

set(SRCS
    "tcpsrv.c"
    "../get_in_addr.c"
    "../tcpopt.c"
    "../../ttoi.c"
    "../../../algorithm/containers/dynamic_array.c"
    )

if(WIN32)
    option(WIN32_USE_IOCP "Using IOCP or not" ON)
    if(WIN32_USE_IOCP)
        set(SRCS ${SRCS} "startsrv_win32_IOCP.c")
    else()
        set(SRCS ${SRCS} "startsrv_win32.c")
    endif()
else()
    set(SRCS ${SRCS} "startsrv_posix.c")
endif()

add_executable(tcpsrv ${SRCS})
