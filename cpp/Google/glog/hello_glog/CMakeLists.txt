cmake_minimum_required(VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

project(hello_glog CXX)

find_package(glog CONFIG REQUIRED)

add_executable(hello_glog "hello_glog.cpp")

target_link_libraries(hello_glog PRIVATE glog::glog)
