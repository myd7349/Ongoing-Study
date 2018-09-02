cmake_minimum_required(VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake")
endif()

project(QuickGuideExample CXX)

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(QuickGuideExample00 "QuickGuideExample00.cpp")
add_executable(QuickGuideExample01 "QuickGuideExample01.cpp")
add_executable(QuickGuideExample02 "QuickGuideExample02.cpp")

# References:
# https://cmake.org/cmake/help/latest/module/FindBoost.html
