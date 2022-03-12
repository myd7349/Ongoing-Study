cmake_minimum_required(VERSION 3.10)

project(flecs_example LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)

find_package(flecs CONFIG REQUIRED)

if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/main.cpp")
    file(DOWNLOAD
        "https://raw.githubusercontent.com/SanderMertens/flecs/v2.4.8/examples/cpp/01_helloworld/src/main.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/main.cpp"
    )
endif()

function(replace_string filename match replace)
    file(READ "${filename}" contents)
    string(REPLACE "${match}" "${replace}" contents "${contents}")
    file(WRITE "${filename}" "${contents}")
endfunction()

replace_string(
    "${CMAKE_CURRENT_BINARY_DIR}/main.cpp"
    "#include <helloworld.h>"
    "#include <flecs.h>"
)

add_executable(helloworld "${CMAKE_CURRENT_BINARY_DIR}/main.cpp")
if(TARGET flecs::flecs_static)
    target_link_libraries(helloworld PRIVATE flecs::flecs_static)
else()
    target_link_libraries(helloworld PRIVATE flecs::flecs)
endif()

# References:
# [How do I activate C++ 11 in CMake?](https://stackoverflow.com/questions/10851247/how-do-i-activate-c-11-in-cmake)
