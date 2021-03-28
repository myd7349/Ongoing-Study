cmake_minimum_required(VERSION 3.8)
project(LaunchSnippingTool C)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:wmainCRTStartup")

set(sources
    LaunchSnippingTool.c
    "${CMAKE_CURRENT_LIST_DIR}/../Execute.c"
    "${CMAKE_CURRENT_LIST_DIR}/../WindowsVersionHelpers.c"
)

add_executable(LaunchSnippingTool ${sources})

target_include_directories(LaunchSnippingTool PRIVATE "${CMAKE_CURRENT_LIST_DIR}/../")
target_compile_definitions(LaunchSnippingTool PRIVATE UNICODE _UNICODE)

# References:
# [What's the equivalent of gcc's -mwindows option in cmake?](https://stackoverflow.com/questions/2752792/whats-the-equivalent-of-gccs-mwindows-option-in-cmake)
# [How to Set C++ Application Entry Point to main() on Windows using CMake?](https://stackoverflow.com/questions/45724766/how-to-set-c-application-entry-point-to-main-on-windows-using-cmake)
