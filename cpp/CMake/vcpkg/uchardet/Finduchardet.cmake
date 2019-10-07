find_path(uchardet_INCLUDE_DIRS NAMES uchardet/uchardet.h)

get_filename_component(_prefix_path ${uchardet_INCLUDE_DIRS} PATH)

find_library(
    uchardet_LIBRARY_DEBUG
    NAMES uchardet
    PATHS ${_prefix_path}/debug/lib
    NO_DEFAULT_PATH
)

find_library(
    uchardet_LIBRARY_RELEASE
    NAMES uchardet
    PATHS ${_prefix_path}/lib
    NO_DEFAULT_PATH
)

unset(_prefix_path)

include(SelectLibraryConfigurations)
select_library_configurations(uchardet)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    uchardet
    REQUIRED_VARS
        uchardet_INCLUDE_DIRS
        uchardet_LIBRARIES
)

mark_as_advanced(
    uchardet_FOUND
    uchardet_INCLUDE_DIRS
    uchardet_LIBRARIES
)

if (NOT TARGET uchardet::uchardet)
    add_library(uchardet::uchardet UNKNOWN IMPORTED)

    set_target_properties(
        uchardet::uchardet
        PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${uchardet_INCLUDE_DIRS}"
    )

    if (uchardet_LIBRARY_RELEASE)
        set_property(
            TARGET uchardet::uchardet
            APPEND PROPERTY
            IMPORTED_CONFIGURATIONS RELEASE
        )
        set_target_properties(
            uchardet::uchardet
            PROPERTIES
                IMPORTED_LOCATION_RELEASE "${uchardet_LIBRARY_RELEASE}"
        )
    endif ()

    if (uchardet_LIBRARY_DEBUG)
        set_property(
            TARGET uchardet::uchardet
            APPEND PROPERTY
            IMPORTED_CONFIGURATIONS DEBUG
        )
        set_target_properties(
            uchardet::uchardet
            PROPERTIES
                IMPORTED_LOCATION_DEBUG "${uchardet_LIBRARY_DEBUG}"
        )
    endif ()

    if (NOT uchardet_LIBRARY_RELEASE AND NOT uchardet_LIBRARY_DEBUG)
        set_property(
            TARGET uchardet::uchardet
            APPEND PROPERTY
            IMPORTED_LOCATION "${uchardet_LIBRARIES}"
        )
    endif ()
endif ()


# References:
# FindBZip2.cmake
