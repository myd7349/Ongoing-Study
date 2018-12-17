# zeromq/czmq/Findlibcurl.cmake

if (NOT MSVC)
    include(FindPkgConfig)
    pkg_check_modules(PC_LIBCURL "libcurl")
    if (PC_LIBCURL_FOUND)
        # add CFLAGS from pkg-config file, e.g. draft api.
        add_definitions(${PC_LIBCURL_CFLAGS} ${PC_LIBCURL_CFLAGS_OTHER})
        # some libraries install the headers is a subdirectory of the include dir
        # returned by pkg-config, so use a wildcard match to improve chances of finding
        # headers and SOs.
        set(PC_LIBCURL_INCLUDE_HINTS ${PC_LIBCURL_INCLUDE_DIRS} ${PC_LIBCURL_INCLUDE_DIRS}/*)
        set(PC_LIBCURL_LIBRARY_HINTS ${PC_LIBCURL_LIBRARY_DIRS} ${PC_LIBCURL_LIBRARY_DIRS}/*)
    endif(PC_LIBCURL_FOUND)
endif (NOT MSVC)

find_path (
    LIBCURL_INCLUDE_DIRS
    NAMES curl/curl.h
    HINTS ${PC_LIBCURL_INCLUDE_HINTS}
)

find_library (
    LIBCURL_LIBRARIES
    # https://stackoverflow.com/questions/37358427/cmake-how-to-link-a-library-which-has-a-lib-prefix-on-windows
    # https://github.com/Microsoft/vcpkg/issues/4312
    NAMES curl libcurl
    HINTS ${PC_LIBCURL_LIBRARY_HINTS}
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    LIBCURL
    REQUIRED_VARS LIBCURL_LIBRARIES LIBCURL_INCLUDE_DIRS
)
mark_as_advanced(
    LIBCURL_FOUND
    LIBCURL_LIBRARIES LIBCURL_INCLUDE_DIRS
)
