cmake_minimum_required(VERSION 3.8)

if(WIN32 AND DEFINED ENV{VCPKG_ROOT}) #AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
    #set(VCPKG_TARGET_TRIPLET x86-windows-static)
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

find_package(ZeroMQ CONFIG REQUIRED)
find_package(czmq CONFIG REQUIRED)

add_executable(ipc_test "ipc_test.c")

if(VCPKG_TARGET_TRIPLET MATCHES "^.+-static$")
    message("Linked to czmq-static.")
    target_link_libraries(ipc_test PRIVATE libzmq-static czmq-static)
else()
    message("Linked to czmq.")
    target_link_libraries(ipc_test PRIVATE libzmq czmq)
endif()

# References:
# https://github.com/Microsoft/vcpkg/blob/master/docs/users/integration.md
# https://blogs.msdn.microsoft.com/vcblog/2016/11/01/vcpkg-updates-static-linking-is-now-available/
