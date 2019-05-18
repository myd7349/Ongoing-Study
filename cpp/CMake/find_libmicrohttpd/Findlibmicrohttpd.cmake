find_path(
    LIBMICROHTTPD_INCLUDE_DIRS
    NAMES microhttpd.h
)

get_filename_component(_prefix_path ${LIBMICROHTTPD_INCLUDE_DIRS} PATH)
message(STATUS "_prefix_path: ${_prefix_path}")

find_library(
    LIBMICROHTTPD_LIBRARY_DEBUG
    NAMES libmicrohttpd microhttpd
    PATHS ${_prefix_path}/debug/lib
    NO_DEFAULT_PATH
)

find_library(
    LIBMICROHTTPD_LIBRARY_RELEASE
    NAMES libmicrohttpd microhttpd
    PATHS ${_prefix_path}/lib
    NO_DEFAULT_PATH
)

include(SelectLibraryConfigurations)
select_library_configurations(LIBMICROHTTPD)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    LIBMICROHTTPD
    REQUIRED_VARS LIBMICROHTTPD_LIBRARIES LIBMICROHTTPD_INCLUDE_DIRS
)


# References:
# https://github.com/zeromq/czmq/blob/master/Findlibmicrohttpd.cmake
# https://github.com/Microsoft/vcpkg/issues/2979
# https://github.com/microsoft/vcpkg/issues/6394
# https://cmake.org/pipermail/cmake/2006-October/011593.html
# https://github.com/microsoft/vcpkg/issues/1626
