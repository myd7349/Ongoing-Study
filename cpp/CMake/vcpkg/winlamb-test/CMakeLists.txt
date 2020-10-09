cmake_minimum_required(VERSION 3.8)

project(winlamb-test CXX)

find_path(WINLAMB_INCLUDE_DIRS "winlamb/window_main.h")

set(CMAKE_WIN32_EXECUTABLE ON)

add_executable(winlamb-test winlamb-test.cpp)
target_include_directories(winlamb-test PRIVATE ${WINLAMB_INCLUDE_DIRS})

# References:
# [How to Set C++ Application Entry Point to main() on Windows using CMake?](https://stackoverflow.com/questions/45724766/how-to-set-c-application-entry-point-to-main-on-windows-using-cmake)
# [What's the equivalent of gcc's -mwindows option in cmake?](https://stackoverflow.com/questions/2752792/whats-the-equivalent-of-gccs-mwindows-option-in-cmake)
