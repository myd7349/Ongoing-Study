cmake_minimum_required(VERSION 3.8)

project(UDPClientDemo CXX)

add_library(
    UDPClient
        "${CMAKE_CURRENT_LIST_DIR}/../Error.h"
        "${CMAKE_CURRENT_LIST_DIR}/../Error.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/../Platform.h"
        "${CMAKE_CURRENT_LIST_DIR}/../Platform.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/../UDPClient.h"
        "${CMAKE_CURRENT_LIST_DIR}/../UDPClient.cpp"
)
target_include_directories(
    UDPClient
    PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/.."
)
if(WIN32)
    target_link_libraries(UDPClient PUBLIC Ws2_32)
endif()


add_subdirectory(Client)
add_subdirectory(Server)
