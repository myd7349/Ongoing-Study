cmake_minimum_required(VERSION 3.8)

project(http-get LANGUAGES C)

find_package(CURL CONFIG REQUIRED)
find_package(yyjson CONFIG REQUIRED)

set(dynarr_root_dir "${CMAKE_CURRENT_LIST_DIR}/../../../algorithm/containers")
add_library(dynarr STATIC "${dynarr_root_dir}/dynamic_array.c")
target_include_directories(dynarr PUBLIC "${dynarr_root_dir}")

add_executable(http-get http-get.c)

target_link_libraries(
    http-get
    PRIVATE
        CURL::libcurl
        yyjson::yyjson
        dynarr
)
