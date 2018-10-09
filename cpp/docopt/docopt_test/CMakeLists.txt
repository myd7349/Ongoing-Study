cmake_minimum_required(VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

project(docopt_test LANGUAGES CXX)

set(VCPKG_TARGET_ARCHITECTURE x86)
#set(VCPKG_CRT_LINKAGE dynamic)
#set(VCPKG_LIBRARY_LINKAGE static)
set(VCPKG_PLATFORM_TOOLSET v141)

find_package(docopt CONFIG REQUIRED)

add_executable(docopt_test "docopt_test.cpp")

target_link_libraries(docopt_test PRIVATE docopt docopt_s)
