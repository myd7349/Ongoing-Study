cmake_minimum_required(VERSION 3.9)

project(parse_version_number C)

file(DOWNLOAD
    "https://raw.githubusercontent.com/GNOME/libxml2/master/configure.ac"
    "${CMAKE_BINARY_DIR}/configure.ac")

file(STRINGS "${CMAKE_BINARY_DIR}/configure.ac"
    _libxml_version_defines REGEX "LIBXML_(MAJOR|MINOR|MICRO)_VERSION=([0-9]+)$")

foreach(ver ${_libxml_version_defines})
    if(ver MATCHES "LIBXML_(MAJOR|MINOR|MICRO)_VERSION=([0-9]+)$")
        set(LIBXML_${CMAKE_MATCH_1}_VERSION "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()

set(VERSION ${LIBXML_MAJOR_VERSION}.${LIBXML_MINOR_VERSION}.${LIBXML_MICRO_VERSION})
math(EXPR LIBXML_VERSION_NUMBER
    "${LIBXML_MAJOR_VERSION} * 10000 + ${LIBXML_MINOR_VERSION} * 100 + ${LIBXML_MICRO_VERSION}")

message(STATUS "LIBXML_MAJOR_VERSION: ${LIBXML_MAJOR_VERSION}")
message(STATUS "LIBXML_MINOR_VERSION: ${LIBXML_MINOR_VERSION}")
message(STATUS "LIBXML_MICRO_VERSION: ${LIBXML_MICRO_VERSION}")
message(STATUS "VERSION: ${VERSION}")
message(STATUS "LIBXML_VERSION_NUMBER: ${LIBXML_VERSION_NUMBER}")

# References:
# vcpkg/ports/libxml2
