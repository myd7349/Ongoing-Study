cmake_minimum_required(VERSION 3.8)

project(inet_pton_test C)

if(WIN32)
    if(MSVC)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS=1 -D_CRT_NONSTDC_NO_DEPRECATE=1)
    endif()

    add_definitions(-DUSING_UNICODE=1)
endif()

option(USE_USER_DEFINED_NTOP_PTON "Using inet_ntop_c/inet_pton_c" ON)

set(SRCS
    "inet_pton_test.c"
    "../ipv4.c"
    "../../getprogname.c"
    "../../../algorithm/string/stringview.c"
    "../../../algorithm/string/substr.c"
    )

if(USE_USER_DEFINED_NTOP_PTON)
    add_definitions(-DUSE_USER_DEFINED_NTOP_PTON=1)
	list(APPEND SRCS
	    "../get_in_addr.c"
	    "../inet_ntop.c"
		"../inet_pton.c"
	    )
else()
    add_definitions(-DUSE_USER_DEFINED_NTOP_PTON=0)
endif()

add_executable(inet_pton_test ${SRCS})
