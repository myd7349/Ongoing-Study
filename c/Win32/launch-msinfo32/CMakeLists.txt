cmake_minimum_required(VERSION 3.8)
project(launch-msinfo32 C)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:wmainCRTStartup")

set(sources
    launch-msinfo32.c
    "${CMAKE_CURRENT_LIST_DIR}/../Execute.c"
    "${CMAKE_CURRENT_LIST_DIR}/../WindowsVersionHelpers.c"
)

add_executable(launch-msinfo32 ${sources})

target_include_directories(launch-msinfo32 PRIVATE "${CMAKE_CURRENT_LIST_DIR}/../")
target_compile_definitions(launch-msinfo32 PRIVATE UNICODE _UNICODE)

# References:
# [What's the equivalent of gcc's -mwindows option in cmake?](https://stackoverflow.com/questions/2752792/whats-the-equivalent-of-gccs-mwindows-option-in-cmake)
# [How to Set C++ Application Entry Point to main() on Windows using CMake?](https://stackoverflow.com/questions/45724766/how-to-set-c-application-entry-point-to-main-on-windows-using-cmake)
