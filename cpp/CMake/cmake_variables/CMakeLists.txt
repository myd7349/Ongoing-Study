cmake_minimum_required(VERSION 3.8)

project(cmake_variables VERSION 1.0.2 LANGUAGES C)

#if (NOT CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
#    set(CPACK_PACKAGING_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")
#elseif (NOT CPACK_PACKAGING_INSTALL_PREFIX)
#    set(CPACK_PACKAGING_INSTALL_PREFIX /usr/local)
#endif ()

set(vars
    CMAKE_C_OUTPUT_EXTENSION
    CMAKE_COMMAND
    CMAKE_CONFIGURATION_TYPES
    CMAKE_CTEST_COMMAND
    CMAKE_EXECUTABLE_SUFFIX
    CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT
    CMAKE_INSTALL_PREFIX
    CMAKE_MODULE_PATH
    CMAKE_PREFIX_PATH
    CMAKE_SYSTEM_NAME
    CMAKE_SYSTEM_PROCESSOR
    CMAKE_VS_PLATFORM_TOOLSET
    CPACK_PACKAGING_INSTALL_PREFIX
    MSVC_IDE
    MSVC_RUNTIME
    MSVC_TOOLSET
    PROJECT_VERSION_MAJOR
    PROJECT_VERSION_MINOR
    PROJECT_VERSION_PATCH
)

foreach (_v ${vars})
    message(STATUS "${_v}: ${${_v}}")
endforeach ()

# References:
# https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html
# https://github.com/KjellKod/g3log/pull/312
# https://stackoverflow.com/questions/5709914/using-cmake-how-do-i-get-verbose-output-from-ctest
# https://github.com/jedisct1/libhydrogen/pull/72
# https://stackoverflow.com/questions/9160335/os-specific-instructions-in-cmake-how-to
# https://stackoverflow.com/questions/27660048/cmake-check-if-mac-os-x-use-apple-or-apple
# https://stackoverflow.com/questions/26434308/cmake-system-name-blank
# https://blog.kitware.com/cmake-and-the-default-build-type/
