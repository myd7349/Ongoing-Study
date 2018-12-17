cmake_minimum_required(VERSION 3.9)

project(pctutil C)

find_package(CURL REQUIRED)

add_executable(pctutil "pctutil.c")

target_link_libraries(pctutil PRIVATE ${CURL_LIBRARIES})
target_include_directories(pctutil PRIVATE ${CURL_INCLUDE_DIRS})
