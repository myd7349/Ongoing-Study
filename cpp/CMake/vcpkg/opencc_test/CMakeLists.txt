cmake_minimum_required(VERSION 3.9)

project(opencc_tests LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

find_package(OpenCC REQUIRED)

get_filename_component(OpenCC_data_path ${OpenCC_INCLUDE_DIRS} PATH)
set(OpenCC_data_path "${OpenCC_data_path}/share/opencc")
message(STATUS "OpenCC_data_path: ${OpenCC_data_path}")

if (WIN32)
    add_library(wconv
        ${CMAKE_CURRENT_LIST_DIR}/../../../../c/Win32/wconv.h
        ${CMAKE_CURRENT_LIST_DIR}/../../../../c/Win32/wconv.c
    )
endif ()

add_executable(opencc_test opencc_test.cpp)
target_compile_definitions(opencc_test PRIVATE OPENCC_DATA_PATH=\"${OpenCC_data_path}/\")
if (MSVC)
    target_compile_options(opencc_test PRIVATE /utf-8)
endif ()
target_link_libraries(opencc_test PRIVATE OpenCC::OpenCC)
if (WIN32)
    target_link_libraries(opencc_test PRIVATE wconv)
endif ()

# References:
# https://docs.microsoft.com/en-us/cpp/build/reference/source-charset-set-source-character-set?view=vs-2019
