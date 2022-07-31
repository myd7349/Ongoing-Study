cmake_minimum_required(VERSION 3.8)

file(STRINGS VERSION.txt PRODUCT_VERSION)

project(get_git_version VERSION ${PRODUCT_VERSION} LANGUAGES C)

function(get_last_commit_hash OUTPUT_VARIABLE)
    find_package(Git QUIET)
    if(Git_FOUND)
        execute_process(
            COMMAND "${GIT_EXECUTABLE}" rev-parse --short HEAD
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
            OUTPUT_VARIABLE LAST_COMMIT_HASH
            OUTPUT_STRIP_TRAILING_WHITESPACE
            RESULT_VARIABLE ERROR_CODE
            ERROR_QUIET
        )

        if(ERROR_CODE EQUAL "0")
            set(${OUTPUT_VARIABLE} ${LAST_COMMIT_HASH} PARENT_SCOPE)
        else()
            set(${OUTPUT_VARIABLE} "rev-unknown" PARENT_SCOPE)
        endif()
    else()
        set(${OUTPUT_VARIABLE} "rev-unknown" PARENT_SCOPE)
    endif()
endfunction()

get_last_commit_hash(GIT_VERSION)

string(TIMESTAMP BUILD_TIME "%Y-%m-%dT%H:%M:%S")
set(BUILD_VERSION "${GIT_VERSION}(${BUILD_TIME})")

message(STATUS "Product version: ${PRODUCT_VERSION}")
message(STATUS "Source version: ${GIT_VERSION}")
message(STATUS "Build version: ${BUILD_VERSION}")

configure_file(
    ${PROJECT_SOURCE_DIR}/GitVersion.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/GitVersion.h
)

set(sources
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/GitVersion.h
)
add_executable(get_git_version main.c)
target_include_directories(
    get_git_version
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

# References:
# https://github.com/microsoft/vcpkg/pull/11460
# [Compile date and time using cmake](https://stackoverflow.com/questions/24292898/compile-date-and-time-using-cmake)
# https://github.com/aseprite/aseprite/blob/main/src/ver/CMakeLists.txt
# https://github.com/sccn/liblsl/blob/master/CMakeLists.txt
# > set(LSL_VERSION_INFO "git:${lslgitrevision}/branch:${lslgitbranch}/build:${CMAKE_BUILD_TYPE}/compiler:${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}")
# > set_source_files_properties("src/buildinfo.cpp"
# >   PROPERTIES COMPILE_DEFINITIONS
# >   LSL_LIBRARY_INFO_STR="${LSL_VERSION_INFO}/link:${LSL_LIB_TYPE}"
# > )
# https://github.com/sccn/liblsl/blob/master/src/buildinfo.cpp
# https://gitlab.com/wireshark/wireshark/-/blob/master/ws_version.h.in
# https://github.com/jonls/redshift/blob/master/src/windows/versioninfo.rc
