cmake_minimum_required(VERSION 3.8.0)

project(json_to_json CXX)

find_package(taocpp-json CONFIG REQUIRED)

file(DOWNLOAD
    "https://raw.githubusercontent.com/taocpp/json/master/src/example/json/json_to_json.cpp"
    "${CMAKE_CURRENT_BINARY_DIR}/json_to_json.cpp"
)

add_executable(json_to_json ${CMAKE_CURRENT_BINARY_DIR}/json_to_json.cpp)
target_link_libraries(json_to_json PRIVATE taocpp::json)
set_target_properties(json_to_json
    PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)
if (MSVC)
    target_compile_options(json_to_json PRIVATE /W4 /WX /utf-8)
else ()
    target_compile_options(json_to_json PRIVATE -pedantic -Wall -Wextra -Wshadow -Werror)
endif ()
