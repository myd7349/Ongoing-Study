cmake_minimum_required(VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

project(taskflow_sample LANGUAGES CXX)

find_package(Cpp-Taskflow CONFIG REQUIRED)

add_executable(taskflow_sample "taskflow_sample.cpp")

target_link_libraries(taskflow_sample PRIVATE Cpp-Taskflow::Cpp-Taskflow)
