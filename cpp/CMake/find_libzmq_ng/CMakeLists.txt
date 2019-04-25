cmake_minimum_required(VERSION 3.8)

project(find_libzmq_ng C)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

message("CMake module path: ${CMAKE_MODULE_PATH}")

if (WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif ()

find_package(libzmq QUIET)

if (LIBZMQ_FOUND)
    message(">> LIBZMQ_FOUND: ${LIBZMQ_FOUND}")
    message(">> LIBZMQ_INCLUDE_DIRS: ${LIBZMQ_INCLUDE_DIRS}")
    message(">> LIBZMQ_LIBRARIES: ${LIBZMQ_LIBRARIES}")
else (LIBZMQ_FOUND)
    message(FATAL_ERROR "libzmq not found." )
endif (LIBZMQ_FOUND)
