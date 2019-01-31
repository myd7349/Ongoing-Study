cmake_minimum_required(VERSION 3.9)

project(parse_version_number)

file(DOWNLOAD
    "https://raw.githubusercontent.com/GNOME/libxml2/master/configure.ac"
    "${CMAKE_SOURCE_DIR}/configure.ac")

set(_config_ac ${CMAKE_SOURCE_DIR}/configure.ac)

file(STRINGS ${_config_ac} _version_lines REGEX "LIBXML_(MAJOR|MINOR|MICRO)_VERSION[^=]*=.*")

string(REGEX REPLACE ".*LIBXML_MAJOR_VERSION=([0-9]+).*" "\\1" _major_version ${_version_lines})
string(REGEX REPLACE ".*LIBXML_MINOR_VERSION=([0-9]+).*" "\\1" _minor_version ${_version_lines})
string(REGEX REPLACE ".*LIBXML_MICRO_VERSION=([0-9]+).*" "\\1" _micro_version ${_version_lines})
string(REGEX REPLACE ".*LIBXML_MICRO_VERSION_SUFFIX=(.*)" "\\1" _micro_version_suffix ${_version_lines})

message("Major version: ${_major_version}")
message("Minor version: ${_minor_version}")
message("Micro version: ${_micro_version}")
message("Micro version suffix: ${_micro_version_suffix}")

set(LIBXML_VERSION ${_major_version}.${_minor_version}.${_micro_version})

message("LIBXML_VERSION: ${LIBXML_VERSION}")

# LIBXML_VERSION_NUMBER=`expr $LIBXML_MAJOR_VERSION \* 10000 + $LIBXML_MINOR_VERSION \* 100 + $LIBXML_MICRO_VERSION`
math(EXPR LIBXML_VERSION_NUMBER
    "${_major_version} * 10000 + ${_minor_version} * 100 + ${_micro_version}")

message("LIBXML_VERSION_NUMBER: ${LIBXML_VERSION_NUMBER}")

# References:
# https://stackoverflow.com/questions/22487215/cmake-function-parameter-and-return
# https://stackoverflow.com/questions/7485227/how-to-increment-variable
# https://github.com/Microsoft/vcpkg/pull/5193
