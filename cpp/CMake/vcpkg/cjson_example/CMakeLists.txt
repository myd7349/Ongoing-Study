cmake_minimum_required(VERSION 3.9)

project(cjson_example C)

find_package(cJSON CONFIG REQUIRED)

add_executable(print_json print_json.c)
target_link_libraries(print_json PRIVATE cjson cjson_utils)
