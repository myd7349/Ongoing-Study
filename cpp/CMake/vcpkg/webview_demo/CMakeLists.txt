cmake_minimum_required(VERSION 3.8)

project(demo001 CXX)

find_path(
    WEBVIEW_INCLUDE_DIRS
    NAMES webview.h
)

add_executable(demo001 "demo001.cpp")
target_include_directories(demo001 PRIVATE ${WEBVIEW_INCLUDE_DIRS})
