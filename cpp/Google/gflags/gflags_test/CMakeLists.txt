cmake_minimum_required(VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

project(gflags_test CXX)

find_package(gflags REQUIRED)

add_executable(gflags_test gflags_test.cpp)

target_link_libraries(gflags_test PRIVATE gflags)
