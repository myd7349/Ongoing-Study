cmake_minimum_required(VERSION 3.8)

project(prettify LANGUAGES C)

find_package(yyjson CONFIG REQUIRED)

include(CheckSymbolExists)

check_symbol_exists(getline "stdio.h" HAVE_GETLINE)

add_executable(prettify prettify.c)
if(HAVE_GETLINE)
    target_compile_definitions(prettify PRIVATE HAVE_GETLINE)
endif()
target_link_libraries(prettify PRIVATE yyjson::yyjson)
