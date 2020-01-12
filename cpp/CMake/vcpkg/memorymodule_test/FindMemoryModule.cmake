find_path(MemoryModule_INCLUDE_DIRS NAMES MemoryModule.h)

get_filename_component(_prefix_path ${MemoryModule_INCLUDE_DIRS} PATH)

find_library(
    MemoryModule_LIBRARY_DEBUG
    NAMES MemoryModule
    PATHS ${_prefix_path}/debug/lib
    NO_DEFAULT_PATH
)

find_library(
    MemoryModule_LIBRARY_RELEASE
    NAMES MemoryModule
    PATHS ${_prefix_path}/lib
    NO_DEFAULT_PATH
)

unset(_prefix_path)

include(SelectLibraryConfigurations)
select_library_configurations(MemoryModule)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    MemoryModule
    REQUIRED_VARS
        MemoryModule_INCLUDE_DIRS
        MemoryModule_LIBRARIES
)

mark_as_advanced(
    MemoryModule_FOUND
    MemoryModule_INCLUDE_DIRS
    MemoryModule_LIBRARIES
)

if (NOT TARGET MemoryModule::MemoryModule)
    add_library(MemoryModule::MemoryModule UNKNOWN IMPORTED)

    set_target_properties(
        MemoryModule::MemoryModule
        PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${MemoryModule_INCLUDE_DIRS}"
    )

    if (MemoryModule_LIBRARY_RELEASE)
        set_property(
            TARGET MemoryModule::MemoryModule
            APPEND PROPERTY
            IMPORTED_CONFIGURATIONS RELEASE
        )
        set_target_properties(
            MemoryModule::MemoryModule
            PROPERTIES
                IMPORTED_LOCATION_RELEASE "${MemoryModule_LIBRARY_RELEASE}"
        )
    endif ()

    if (MemoryModule_LIBRARY_DEBUG)
        set_property(
            TARGET MemoryModule::MemoryModule
            APPEND PROPERTY
            IMPORTED_CONFIGURATIONS DEBUG
        )
        set_target_properties(
            MemoryModule::MemoryModule
            PROPERTIES
                IMPORTED_LOCATION_DEBUG "${MemoryModule_LIBRARY_DEBUG}"
        )
    endif ()

    if (NOT MemoryModule_LIBRARY_RELEASE AND NOT MemoryModule_LIBRARY_DEBUG)
        set_property(
            TARGET MemoryModule::MemoryModule
            APPEND PROPERTY
            IMPORTED_LOCATION "${MemoryModule_LIBRARIES}"
        )
    endif ()
endif ()


# References:
# FindBZip2.cmake
