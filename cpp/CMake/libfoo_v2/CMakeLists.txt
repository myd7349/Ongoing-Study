cmake_minimum_required(VERSION 3.8)

project(libfoo VERSION 2.1.0 LANGUAGES C)

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    if (NOT CPACK_PACKAGING_INSTALL_PREFIX)
        if (NOT CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
            set(CPACK_PACKAGING_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")
        else ()
            set(CPACK_PACKAGING_INSTALL_PREFIX "/usr/local" CACHE PATH "..." FORCE)
        endif ()
    endif ()
endif ()

include(CTest)
include(InstallRequiredSystemLibraries)

option(BUILD_SHARED_LIBS "Build shared library." ${BUILD_SHARED_LIBS})
option(BUILD_STATIC_LIBS "Build static library (default if BUILD_SHARED_LIBS is OFF)." ON)

if (NOT BUILD_SHARED_LIBS AND NOT BUILD_STATIC_LIBS)
    set(BUILD_STATIC_LIBS ON)
endif ()

add_subdirectory(src)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif ()

set(CPACK_PACKAGE_NAME "libfoo_v2")
set(CPACK_PACKAGE_VENDOR "myd7349")
set(CPACK_PACKAGE_CONTACT "myd7349 myd7349@gmail.com")
set(CMAKE_PROJECT_HOMEPAGE_URL "https://github.com/myd7349/Ongoing-Study" )
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "libfoo_v2: A CMake example")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_FILE_NAME "libfoo_v2-${PROJECT_VERSION}$ENV{RAYLIB_PACKAGE_SUFFIX}")
set(CPACK_GENERATOR "DEB;ZIP;TGZ") # NSIS

include(CPack)

# References:
# https://github.com/raysan5/raylib/blob/master/src/CMakeLists.txt
# https://github.com/KjellKod/g3log/pull/312
# https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT.html
