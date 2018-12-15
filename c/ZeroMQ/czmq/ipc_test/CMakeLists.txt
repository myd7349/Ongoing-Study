cmake_minimum_required(VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

project(ipc_test C)

option(TEST_IPC "Test IPC" ON)
if(TEST_IPC)
    add_definitions(-DTEST_IPC=1)
    add_definitions(-DTEST_INPROC=0)
else()
    add_definitions(-DTEST_IPC=0)
    add_definitions(-DTEST_INPROC=1)
endif()

find_package(czmq CONFIG REQUIRED)

add_executable(ipc_test "ipc_test.c")

target_link_libraries(ipc_test PRIVATE czmq)
