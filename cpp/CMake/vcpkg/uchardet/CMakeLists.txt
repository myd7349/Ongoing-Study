cmake_minimum_required(VERSION 3.9)

project(uchardet LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

find_package(uchardet REQUIRED)

add_executable(uchardet uchardet.c)
target_link_libraries(uchardet PRIVATE uchardet::uchardet)
