cmake_minimum_required(VERSION 3.9)

project(parse_version_number C)

set(_package_version_re
    "#define[ ]+PACKAGE_VERSION[ ]+\"([0-9]+.[0-9]+.[0-9]+)\""
)

file(STRINGS "${CMAKE_CURRENT_LIST_DIR}/config.h"
    _package_version_define REGEX "${_package_version_re}"
)

string(REGEX REPLACE "${_package_version_re}" "\\1" PACKAGE_VERSION ${_package_version_define})

message(STATUS "_package_version_define: ${_package_version_define}")
message(STATUS "PACKAGE_VERSION: ${PACKAGE_VERSION}")


# References:
# https://github.com/EOSIO/fc/blob/master/GitVersionGen/GetGitRevisionDescription.cmake.in
