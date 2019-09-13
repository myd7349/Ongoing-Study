find_path(LIBXLSXWRITER_INCLUDE_DIRS NAMES xlsxwriter.h)

get_filename_component(_prefix_path ${LIBXLSXWRITER_INCLUDE_DIRS} PATH)

find_library(
    LIBXLSXWRITER_LIBRARY_DEBUG
    NAMES xlsxwriter
    PATHS ${_prefix_path}/debug/lib
    NO_DEFAULT_PATH
)

find_library(
    LIBXLSXWRITER_LIBRARY_RELEASE
    NAMES xlsxwriter
    PATHS ${_prefix_path}/lib
    NO_DEFAULT_PATH
)

unset(_prefix_path)

include(SelectLibraryConfigurations)
select_library_configurations(LIBXLSXWRITER)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    LIBXLSXWRITER
    REQUIRED_VARS
        LIBXLSXWRITER_INCLUDE_DIRS
        LIBXLSXWRITER_LIBRARIES
)

mark_as_advanced(
    LIBXLSXWRITER_FOUND
    LIBXLSXWRITER_INCLUDE_DIRS
    LIBXLSXWRITER_LIBRARIES
)
