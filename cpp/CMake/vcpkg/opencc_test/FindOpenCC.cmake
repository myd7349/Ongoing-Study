find_path(OpenCC_INCLUDE_DIRS NAMES opencc/opencc.h)

get_filename_component(_prefix_path ${OpenCC_INCLUDE_DIRS} PATH)

find_library(
    OpenCC_LIBRARY_DEBUG
    NAMES opencc
    PATHS ${_prefix_path}/debug/lib
    NO_DEFAULT_PATH
)

find_library(
    OpenCC_LIBRARY_RELEASE
    NAMES opencc
    PATHS ${_prefix_path}/lib
    NO_DEFAULT_PATH
)

unset(_prefix_path)

include(SelectLibraryConfigurations)
select_library_configurations(OpenCC)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    OpenCC
    REQUIRED_VARS
        OpenCC_INCLUDE_DIRS
        OpenCC_LIBRARIES
)

mark_as_advanced(
    OpenCC_FOUND
    OpenCC_INCLUDE_DIRS
    OpenCC_LIBRARIES
)

if (NOT TARGET OpenCC::OpenCC)
    add_library(OpenCC::OpenCC UNKNOWN IMPORTED)

    set_target_properties(
        OpenCC::OpenCC
        PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${OpenCC_INCLUDE_DIRS}"
    )

    if (OpenCC_LIBRARY_RELEASE)
        set_property(
            TARGET OpenCC::OpenCC
            APPEND PROPERTY
            IMPORTED_CONFIGURATIONS RELEASE
        )
        set_target_properties(
            OpenCC::OpenCC
            PROPERTIES
                IMPORTED_LOCATION_RELEASE "${OpenCC_LIBRARY_RELEASE}"
        )
    endif ()

    if (OpenCC_LIBRARY_DEBUG)
        set_property(
            TARGET OpenCC::OpenCC
            APPEND PROPERTY
            IMPORTED_CONFIGURATIONS DEBUG
        )
        set_target_properties(
            OpenCC::OpenCC
            PROPERTIES
                IMPORTED_LOCATION_DEBUG "${OpenCC_LIBRARY_DEBUG}"
        )
    endif ()

    if (NOT OpenCC_LIBRARY_RELEASE AND NOT OpenCC_LIBRARY_DEBUG)
        set_property(
            TARGET OpenCC::OpenCC
            APPEND PROPERTY
            IMPORTED_LOCATION "${OpenCC_LIBRARIES}"
        )
    endif ()
endif ()


# References:
# FindBZip2.cmake
