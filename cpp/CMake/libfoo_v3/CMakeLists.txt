cmake_minimum_required(VERSION 3.8)

project(libfoo VERSION 3.2.1 LANGUAGES C)

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

set(CPACK_PACKAGE_NAME "libfoo_v3")
set(CPACK_PACKAGE_VENDOR "myd7349")
set(CPACK_PACKAGE_CONTACT "myd7349 myd7349@gmail.com")
set(CMAKE_PROJECT_HOMEPAGE_URL "https://github.com/myd7349/Ongoing-Study" )
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "libfoo_v3: A CMake example")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_FILE_NAME "libfoo_v3-${PROJECT_VERSION}$ENV{RAYLIB_PACKAGE_SUFFIX}")
set(CPACK_GENERATOR "DEB;ZIP;TGZ") # NSIS

include(CPack)
