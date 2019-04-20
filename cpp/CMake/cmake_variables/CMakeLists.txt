cmake_minimum_required(VERSION 3.8)

project(cmake_variables VERSION 1.0.2 LANGUAGES C)

#if (NOT CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
#    set(CPACK_PACKAGING_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")
#elseif (NOT CPACK_PACKAGING_INSTALL_PREFIX)
#    set(CPACK_PACKAGING_INSTALL_PREFIX /usr/local)
#endif ()

set(vars
    CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT
    CMAKE_INSTALL_PREFIX
    CMAKE_MODULE_PATH
    CMAKE_PREFIX_PATH
    CPACK_PACKAGING_INSTALL_PREFIX
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
