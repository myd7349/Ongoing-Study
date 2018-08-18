cmake_minimum_required (VERSION 3.8)
project ("hostinfo")

option(OLD_SCHOOL_STYLE "Use old-school style or not" OFF)
if(OLD_SCHOOL_STYLE)
    add_definitions(-DOLD_SCHOOL_STYLE)
endif()

add_executable (hostinfo "hostinfo.c")
