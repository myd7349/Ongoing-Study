cmake_minimum_required(VERSION 3.9)

project(pctutil C)

find_package(CURL CONFIG REQUIRED)

option(AVOID_CURL_FREE_OUTSIDE "Avoid calling curl_free outside." ON)
option(ENABLE_WCONV "Enable wconv." ON)

set(MAXMIMUM_LINE_LENGTH "1024" CACHE STRING "Maximum line length.")
set(DEFAULT_METHOD "ESCAPE" CACHE STRING "Default method.")

include(CheckSymbolExists)

check_symbol_exists(getline "stdio.h" HAVE_GETLINE)
check_symbol_exists(strdup "string.h" HAVE_STRDUP)
check_symbol_exists(_strdup "string.h" HAVE__STRDUP)
check_symbol_exists(getopt_long "unistd.h" HAVE_GETOPT_LONG)

# On Windows with MSVC, `getopt_long` is not available by default.
# But some third-party libraries can be used. For example, in `vcpkg`,
# we can find a port named `getopt-win32`.
if(NOT HAVE_GETOPT_LONG)
    find_path(GETOPT_INCLUDE_DIR NAMES getopt.h)
    check_symbol_exists(getopt_long "${GETOPT_INCLUDE_DIR}/getopt.h" HAVE_GETOPT_LONG_WIN32)
    find_library(GETOPT_LIBRARY NAMES getopt)
endif()

set(strdup_root_dir "${CMAKE_CURRENT_LIST_DIR}/../..")
add_library(strdup STATIC "${strdup_root_dir}/strdup.c")
target_include_directories(strdup PUBLIC "${strdup_root_dir}")

if(HAVE_STRDUP)
    if(MSVC AND HAVE__STRDUP)
        target_compile_definitions(strdup PUBLIC HAVE__STRDUP)
    else()
        target_compile_definitions(strdup PUBLIC HAVE_STRDUP)
    endif()
elseif(HAVE__STRDUP)
    target_compile_definitions(strdup PUBLIC HAVE__STRDUP)
endif()

add_executable(pctutil pctutil.c)
target_link_libraries(pctutil PRIVATE CURL::libcurl strdup)

if(HAVE_GETLINE)
    target_compile_definitions(pctutil PRIVATE HAVE_GETLINE)
endif()

if(AVOID_CURL_FREE_OUTSIDE)
    target_compile_definitions(pctutil PRIVATE AVOID_CURL_FREE_OUTSIDE)
endif()

if(ENABLE_WCONV)
    set(wconv_root_dir "${CMAKE_CURRENT_LIST_DIR}/../../Win32")
    add_library(wconv STATIC "${wconv_root_dir}/wconv.c")
    target_include_directories(wconv PUBLIC "${wconv_root_dir}")
    target_compile_definitions(pctutil PRIVATE ENABLE_WCONV)
    target_link_libraries(pctutil PRIVATE wconv)
endif()

target_compile_definitions(pctutil PRIVATE MAXMIMUM_LINE_LENGTH=${MAXMIMUM_LINE_LENGTH})
target_compile_definitions(pctutil PRIVATE DEFAULT_METHOD=${DEFAULT_METHOD})

if(HAVE_GETOPT_LONG)
    target_compile_definitions(pctutil PRIVATE HAVE_GETOPT_LONG)
endif()

if(GETOPT_INCLUDE_DIR AND GETOPT_LIBRARY AND HAVE_GETOPT_LONG_WIN32)
    target_include_directories(pctutil PRIVATE ${GETOPT_INCLUDE_DIR})
    target_compile_definitions(pctutil PRIVATE HAVE_GETOPT_LONG_WIN32)
    target_link_libraries(pctutil PRIVATE ${GETOPT_LIBRARY})
endif()
