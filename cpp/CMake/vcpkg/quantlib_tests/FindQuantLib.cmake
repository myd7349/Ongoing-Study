find_path(QUANTLIB_INCLUDE_DIRS NAMES ql/quantlib.hpp)

function (get_msvc_toolset output_variable)
    if (CMAKE_VS_PLATFORM_TOOLSET)
        string(REPLACE v vc msvc_toolset ${CMAKE_VS_PLATFORM_TOOLSET})
        set(msvc_toolset "-${msvc_toolset}")
    elseif (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.10)
        set(msvc_toolset "-vc141")
    elseif(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19)
        set(msvc_toolset "-vc140")
    elseif(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 18)
        set(msvc_toolset "-vc120")
    elseif(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 17)
        set(msvc_toolset "-vc110")
    elseif(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 16)
        set(msvc_toolset "-vc100")
    else()
        message(FATAL_ERROR "Compiler below VC++2010 is not supported")
    endif()

    set(${output_variable} ${msvc_toolset} PARENT_SCOPE)
endfunction ()

if (MSVC)
    get_msvc_toolset(QL_MSVC_TOOLSET)

    message(STATUS "MSVC Toolset: ${QL_MSVC_TOOLSET}")

    set(quantlib_debug_names
        "QuantLib${QL_MSVC_TOOLSET}-mt-gd"
        "QuantLib${QL_MSVC_TOOLSET}-x64-mt-sgd"
    )
    set(quantlib_release_names
        "QuantLib${QL_MSVC_TOOLSET}-mt"
        "QuantLib${QL_MSVC_TOOLSET}-x64-mt-s"
    )

    find_library(QUANTLIB_LIBRARY_DEBUG NAMES ${quantlib_debug_names})
    find_library(QUANTLIB_LIBRARY_RELEASE NAMES ${quantlib_release_names})

    include(SelectLibraryConfigurations)
    select_library_configurations(QUANTLIB)
endif ()

if (NOT QUANTLIB_LIBRARIES)
    find_library(QUANTLIB_LIBRARIES NAMES QuantLib)
endif ()

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    QUANTLIB
    REQUIRED_VARS QUANTLIB_LIBRARIES QUANTLIB_INCLUDE_DIRS
)
mark_as_advanced(
    QUANTLIB_FOUND
    QUANTLIB_INCLUDE_DIRS
    QUANTLIB_LIBRARIES
)


# References:
# https://github.com/lballabio/QuantLib/blob/f09141b5cce9134c0bcdbaf36e81359e6ba30705/cmake/quantlib.cmake#L11-L23
# https://github.com/lballabio/QuantLib/pull/660
