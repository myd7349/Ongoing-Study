cmake_minimum_required(VERSION 3.8)

project(http-get LANGUAGES C CXX)

find_package(CURL CONFIG REQUIRED)
find_package(yyjson CONFIG REQUIRED)

option(WCONV_SUPPORT "Enable wconv support." ON)

add_executable(http-get http-get.cpp)
target_link_libraries(http-get PRIVATE CURL::libcurl yyjson::yyjson)

if(WCONV_SUPPORT)
    set(wconv_root_dir "${CMAKE_CURRENT_LIST_DIR}/../../../c/Win32")
    add_library(wconv STATIC "${wconv_root_dir}/wconv.c")
    target_include_directories(wconv PUBLIC "${wconv_root_dir}")

    target_compile_definitions(http-get PRIVATE WCONV_SUPPORT)
    target_link_libraries(http-get PRIVATE wconv)
endif()
