cmake_minimum_required(VERSION 3.8)

project(list_test VERSION 1.0.2 LANGUAGES CXX)

# https://github.com/amrayn/licensepp/blob/0b6d669c0b323be004f73d8c811d38158ce8c0c7/CMakeLists.txt#L38-L42
if(MSVC)
    list(APPEND CMAKE_CXX_FLAGS " -std=c++11 -O3 ")
else()
    list(APPEND CMAKE_CXX_FLAGS " -std=c++11 -O3 -Wall -Werror ")
endif()

# CMAKE_CXX_FLAGS: /DWIN32 /D_WINDOWS /W3 /GR /EHsc; -std=c++11 -O3
# fatal error C1083: Cannot open source file: ';': No such file or directory
message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

set(CMAKE_CXX_FLAGS)
list(APPEND CMAKE_CXX_FLAGS -std=c++11 -O3)
message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

set(CMAKE_CXX_FLAGS)
string(APPEND CMAKE_CXX_FLAGS " -std=c++11 -O3 ")
message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

set(CMAKE_CXX_FLAGS)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

# References:
# https://stackoverflow.com/questions/35847655/when-should-i-quote-cmake-variables
# https://stackoverflow.com/questions/11594905/how-do-i-correctly-pass-cmake-list-semicolon-sep-of-flags-to-set-target-proper
# https://stackoverflow.com/questions/29901352/appending-to-cmake-c-flags
