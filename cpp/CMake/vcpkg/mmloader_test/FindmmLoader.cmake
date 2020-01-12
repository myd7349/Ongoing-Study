find_path(mmLoader_INCLUDE_DIRS NAMES mmLoader/mmLoader.h)

get_filename_component(_prefix_path ${mmLoader_INCLUDE_DIRS} PATH)

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(current_platform x64)
else ()
    set(current_platform x86)
endif ()

set(mmLoader_library_name "mmLoader-static-${current_platform}-v${MSVC_TOOLSET_VERSION}")
message(STATUS "mmLoader_library_name: ${mmLoader_library_name}")
message(STATUS "mmLoader_INCLUDE_DIRS: ${mmLoader_INCLUDE_DIRS}")

find_library(
    mmLoader_LIBRARY_DEBUG
    NAMES ${mmLoader_library_name}-d
    PATHS ${_prefix_path}/debug/lib
    NO_DEFAULT_PATH
)

find_library(
    mmLoader_LIBRARY_RELEASE
    NAMES ${mmLoader_library_name}
    PATHS ${_prefix_path}/lib
    NO_DEFAULT_PATH
)

message(STATUS "mmLoader_LIBRARY_DEBUG: ${mmLoader_LIBRARY_DEBUG}")
message(STATUS "mmLoader_LIBRARY_RELEASE: ${mmLoader_LIBRARY_RELEASE}")

unset(_prefix_path)

include(SelectLibraryConfigurations)
select_library_configurations(mmLoader)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    mmLoader
    REQUIRED_VARS
        mmLoader_INCLUDE_DIRS
        mmLoader_LIBRARIES
)

mark_as_advanced(
    mmLoader_FOUND
    mmLoader_INCLUDE_DIRS
    mmLoader_LIBRARIES
)

if (NOT TARGET mmLoader::mmLoader)
    add_library(mmLoader::mmLoader UNKNOWN IMPORTED)

    set_target_properties(
        mmLoader::mmLoader
        PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${mmLoader_INCLUDE_DIRS}"
    )

    if (mmLoader_LIBRARY_RELEASE)
        set_property(
            TARGET mmLoader::mmLoader
            APPEND PROPERTY
            IMPORTED_CONFIGURATIONS RELEASE
        )
        set_target_properties(
            mmLoader::mmLoader
            PROPERTIES
                IMPORTED_LOCATION_RELEASE "${mmLoader_LIBRARY_RELEASE}"
        )
    endif ()

    if (mmLoader_LIBRARY_DEBUG)
        set_property(
            TARGET mmLoader::mmLoader
            APPEND PROPERTY
            IMPORTED_CONFIGURATIONS DEBUG
        )
        set_target_properties(
            mmLoader::mmLoader
            PROPERTIES
                IMPORTED_LOCATION_DEBUG "${mmLoader_LIBRARY_DEBUG}"
        )
    endif ()

    if (NOT mmLoader_LIBRARY_RELEASE AND NOT mmLoader_LIBRARY_DEBUG)
        set_property(
            TARGET mmLoader::mmLoader
            APPEND PROPERTY
            IMPORTED_LOCATION "${mmLoader_LIBRARIES}"
        )
    endif ()
endif ()

message(STATUS "mmLoader_LIBRARIES: ${mmLoader_LIBRARIES}")

# References:
# FindBZip2.cmake
