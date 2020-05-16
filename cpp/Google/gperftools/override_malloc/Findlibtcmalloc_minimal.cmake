find_path(libtcmalloc_minimal_INCLUDE_DIRS NAMES gperftools/tcmalloc.h)

get_filename_component(_prefix_path ${libtcmalloc_minimal_INCLUDE_DIRS} PATH)

find_library(
    libtcmalloc_minimal_LIBRARY_DEBUG
    NAMES libtcmalloc_minimal tcmalloc_minimal
    PATHS ${_prefix_path}/debug/lib
    NO_DEFAULT_PATH
)

find_library(
    libtcmalloc_minimal_LIBRARY_RELEASE
    NAMES libtcmalloc_minimal tcmalloc_minimal
    PATHS ${_prefix_path}/lib
    NO_DEFAULT_PATH
)

unset(_prefix_path)

include(SelectLibraryConfigurations)
select_library_configurations(libtcmalloc_minimal)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    libtcmalloc_minimal
    REQUIRED_VARS
        libtcmalloc_minimal_INCLUDE_DIRS
        libtcmalloc_minimal_LIBRARIES
)

mark_as_advanced(
    libtcmalloc_minimal_FOUND
    libtcmalloc_minimal_INCLUDE_DIRS
    libtcmalloc_minimal_LIBRARIES
)

if(NOT TARGET libtcmalloc_minimal::libtcmalloc_minimal)
    add_library(libtcmalloc_minimal::libtcmalloc_minimal UNKNOWN IMPORTED)

    set_target_properties(
        libtcmalloc_minimal::libtcmalloc_minimal
        PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${libtcmalloc_minimal_INCLUDE_DIRS}"
    )

    if(libtcmalloc_minimal_LIBRARY_RELEASE)
        set_property(
            TARGET libtcmalloc_minimal::libtcmalloc_minimal
            APPEND PROPERTY
            IMPORTED_CONFIGURATIONS RELEASE
        )
        set_target_properties(
            libtcmalloc_minimal::libtcmalloc_minimal
            PROPERTIES
                IMPORTED_LOCATION_RELEASE "${libtcmalloc_minimal_LIBRARY_RELEASE}"
        )
    endif()

    if(libtcmalloc_minimal_LIBRARY_DEBUG)
        set_property(
            TARGET libtcmalloc_minimal::libtcmalloc_minimal
            APPEND PROPERTY
            IMPORTED_CONFIGURATIONS DEBUG
        )
        set_target_properties(
            libtcmalloc_minimal::libtcmalloc_minimal
            PROPERTIES
                IMPORTED_LOCATION_DEBUG "${libtcmalloc_minimal_LIBRARY_DEBUG}"
        )
    endif()

    if(NOT libtcmalloc_minimal_LIBRARY_RELEASE AND NOT libtcmalloc_minimal_LIBRARY_DEBUG)
        set_property(
            TARGET libtcmalloc_minimal::libtcmalloc_minimal
            APPEND PROPERTY
            IMPORTED_LOCATION "${libtcmalloc_minimal_LIBRARIES}"
        )
    endif()

    set_target_properties(
        libtcmalloc_minimal::libtcmalloc_minimal
        PROPERTIES LINKER_LANGUAGE CXX
    )
endif()
