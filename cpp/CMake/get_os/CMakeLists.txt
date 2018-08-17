cmake_minimum_required(VERSION 2.8)

project(get_os C)

set(SRCS "get_os.c")

if(WIN32)
    set(SRCS ${SRCS} "get_os_win32.c")
else()
    set(SRCS ${SRCS} "get_os_posix.c")
endif()

message("---- Sources ----")
message("${SRCS}")


add_executable(get_os ${SRCS})

# References:
# https://github.com/Microsoft/cpprestsdk/blob/master/Release/CMakeLists.txt
