vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO gperftools/gperftools
    REF fe62a0baab87ba3abca12f4a621532bf67c9a7d2
    SHA512 fc0fb2c56d38046ac7bc2d36863dabf073b7aede7ce18916228d7b9f64cf33ae754708bff028353ada52bf4b79a7cd3e3334c1558a9ba64b06326b1537faf690
    HEAD_REF master
)

if(VCPKG_TARGET_IS_WINDOWS)
    if(override IN_LIST FEATURES)
        if(VCPKG_LIBRARY_LINKAGE STREQUAL dynamic)
            message(STATUS "${PORT}[override] only supports static library linkage. Building static library.")
            set(VCPKG_LIBRARY_LINKAGE static)
        endif()

        set(libtcmalloc_minimal_release_configuration Release-Override)
    else()
        set(libtcmalloc_minimal_release_configuration Release-Patch)
    endif()

    if(VCPKG_LIBRARY_LINKAGE STREQUAL static)
        set(ENV{CL} "/DPERFTOOLS_DLL_DECL=")
    endif()

    vcpkg_build_msbuild(
        PROJECT_PATH ${SOURCE_PATH}/vsprojects/libtcmalloc_minimal/libtcmalloc_minimal.vcxproj
        DEBUG_CONFIGURATION Debug
        RELEASE_CONFIGURATION ${libtcmalloc_minimal_release_configuration}
    )

    file(COPY
        ${SOURCE_PATH}/src/gperftools/heap-checker.h
        ${SOURCE_PATH}/src/gperftools/heap-profiler.h
        ${SOURCE_PATH}/src/gperftools/malloc_extension.h
        ${SOURCE_PATH}/src/gperftools/malloc_extension_c.h
        ${SOURCE_PATH}/src/gperftools/malloc_hook.h
        ${SOURCE_PATH}/src/gperftools/malloc_hook_c.h
        ${SOURCE_PATH}/src/gperftools/nallocx.h
        ${SOURCE_PATH}/src/gperftools/profiler.h
        ${SOURCE_PATH}/src/gperftools/stacktrace.h
        ${SOURCE_PATH}/src/windows/gperftools/tcmalloc.h
        DESTINATION ${CURRENT_PACKAGES_DIR}/include/gperftools
    )

    file(COPY
        ${SOURCE_PATH}/vsprojects/libtcmalloc_minimal/Debug/libtcmalloc_minimal.lib
        DESTINATION ${CURRENT_PACKAGES_DIR}/debug/lib
    )
    file(COPY
        ${SOURCE_PATH}/vsprojects/libtcmalloc_minimal/${libtcmalloc_minimal_release_configuration}/libtcmalloc_minimal.lib
        DESTINATION ${CURRENT_PACKAGES_DIR}/lib
    )

    if (VCPKG_LIBRARY_LINKAGE STREQUAL dynamic)
        file(COPY
            ${SOURCE_PATH}/vsprojects/libtcmalloc_minimal/Debug/libtcmalloc_minimal.dll
            DESTINATION ${CURRENT_PACKAGES_DIR}/debug/bin
        )
        file(COPY
            ${SOURCE_PATH}/vsprojects/libtcmalloc_minimal/${libtcmalloc_minimal_release_configuration}/libtcmalloc_minimal.dll
            DESTINATION ${CURRENT_PACKAGES_DIR}/bin
        )

        vcpkg_copy_pdbs()
    endif()
else()
    vcpkg_configure_make(
        SOURCE_PATH ${SOURCE_PATH}
        AUTOCONFIG
    )

    vcpkg_install_make()
endif()

configure_file(${SOURCE_PATH}/COPYING ${CURRENT_PACKAGES_DIR}/share/${PORT}/copyright COPYONLY)
