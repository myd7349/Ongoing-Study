cmake_minimum_required(VERSION 3.8)

project(libfoo C)

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

set(CPACK_PACKAGE_VENDOR "myd7349")
set(CMAKE_PROJECT_HOMEPAGE_URL "https://github.com/myd7349/Ongoing-Study" )

include(CPack)
