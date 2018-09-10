cmake_minimum_required(VERSION 3.8)

project(inet_pton_test C)

if(WIN32)
    if(MSVC)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS=1 -D_CRT_NONSTDC_NO_DEPRECATE=1)
    endif()

    #add_definitions(-DUSING_UNICODE=0)
endif()

add_executable(inet_pton_test
    "inet_pton_test.c"
    "../ipv4.c"
    "../../getprogname.c"
    "../../../algorithm/string/stringview.c"
    "../../../algorithm/string/substr.c"
    )
