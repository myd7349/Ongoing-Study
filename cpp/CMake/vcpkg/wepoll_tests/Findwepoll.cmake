find_path(WEPOLL_INCLUDE_DIRS NAMES wepoll.h)

get_filename_component(_prefix_path ${WEPOLL_INCLUDE_DIRS} PATH)

find_library(
    WEPOLL_LIBRARY_DEBUG
    NAMES wepoll
    PATHS ${_prefix_path}/debug/lib
    NO_DEFAULT_PATH
)

find_library(
    WEPOLL_LIBRARY_RELEASE
    NAMES wepoll
    PATHS ${_prefix_path}/lib
    NO_DEFAULT_PATH
)

unset(_prefix_path)

include(SelectLibraryConfigurations)
select_library_configurations(WEPOLL)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    wepoll
	FOUND_VAR WEPOLL_FOUND
    REQUIRED_VARS
        WEPOLL_INCLUDE_DIRS
        WEPOLL_LIBRARIES
)

mark_as_advanced(
    WEPOLL_FOUND
    WEPOLL_INCLUDE_DIRS
    WEPOLL_LIBRARIES
)
