option(SHARED "Build raylib as a dynamic library" OFF)
option(STATIC "Build raylib as a static library" ON)

if(NOT (STATIC OR SHARED))
    message(FATAL_ERROR "Nothing to do if both -DSHARED=OFF and -DSTATIC=OFF...")
endif()

if (DEFINED BUILD_SHARED_LIBS)
    set(SHARED ${BUILD_SHARED_LIBS})
    if (${BUILD_SHARED_LIBS})
        set(STATIC OFF)
    else()
        set(STATIC ON)
    endif()
endif()

# Get the sources together
file(GLOB raylib_sources *.c)

if(STATIC)
    add_library(raylib_static STATIC ${raylib_sources})

    if(NOT WIN32) # Keep lib*.(a|dll) name, but avoid *.lib files overwriting each other on Windows
        set_target_properties(raylib_static PROPERTIES OUTPUT_NAME raylib)
    endif()
endif(STATIC)

if(SHARED)
    add_library(raylib SHARED ${raylib_sources})

    if (MSVC OR REPRODUCE_CI_BUILD_ERROR)
        target_compile_definitions(raylib
            PRIVATE $<BUILD_INTERFACE:BUILD_LIBTYPE_SHARED>
            INTERFACE $<INSTALL_INTERFACE:USE_LIBTYPE_SHARED>
        )
    endif ()

    set_property(TARGET raylib PROPERTY POSITION_INDEPENDENT_CODE ON)
else(SHARED)
    add_library(raylib ALIAS raylib_static)
endif(SHARED)

