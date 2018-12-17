cmake_minimum_required(VERSION 3.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

message("CMake module path: ${CMAKE_MODULE_PATH}")

if (WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif ()

find_package(libcurl REQUIRED)
if (LIBCURL_FOUND)
    message(">> LIBCURL_INCLUDE_DIRS: ${LIBCURL_INCLUDE_DIRS}")
    message(">> LIBCURL_LIBRARIES: ${LIBCURL_LIBRARIES}")
else (LIBCURL_FOUND)
    message(FATAL_ERROR "libcurl not found." )
endif (LIBCURL_FOUND)
