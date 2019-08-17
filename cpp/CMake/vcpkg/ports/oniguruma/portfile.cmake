include(vcpkg_common_functions)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO kkos/oniguruma
    REF v6.9.3
    SHA512 a0f4da26ba08de516c05b5e4b803a9cf8013489c3743ecf27fbc3f66f835eef8fca81b9ed2bd68729a470fe897994046843a4fd31d44a9584ff8dabd1748df21
    HEAD_REF master
)

vcpkg_check_features(OUT_FEATURE_OPTIONS FEATURE_OPTIONS
    INVERTED_FEATURES
        "non-posix" ENABLE_POSIX_API
)

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    PREFER_NINJA
    OPTIONS
        ${FEATURE_OPTIONS}
)

vcpkg_install_cmake()

vcpkg_copy_pdbs()

vcpkg_fixup_cmake_targets(CONFIG_PATH lib/cmake/${PORT})

file(REMOVE_RECURSE
    ${CURRENT_PACKAGES_DIR}/debug/include
    ${CURRENT_PACKAGES_DIR}/debug/share
)

if(VCPKG_TARGET_IS_WINDOWS AND VCPKG_LIBRARY_LINKAGE STREQUAL static)
    vcpkg_replace_string(
        "${CURRENT_PACKAGES_DIR}/include/oniguruma.h"
        "#ifndef ONIG_STATIC"
        "#if 0 // #ifndef ONIG_STATIC"
    )

    if(EXISTS "${CURRENT_PACKAGES_DIR}/include/onigposix.h")
        vcpkg_replace_string(
            "${CURRENT_PACKAGES_DIR}/include/onigposix.h"
[[
#ifndef ONIG_EXTERN
#if defined(_WIN32) && !defined(__GNUC__)
]]
[[
#ifndef ONIG_EXTERN
#if 0 // #if defined(_WIN32) && !defined(__GNUC__)
]]
        )
    endif()
endif()

# Handle copyright
configure_file(${SOURCE_PATH}/COPYING ${CURRENT_PACKAGES_DIR}/share/${PORT}/copyright COPYONLY)

# CMake integration test
vcpkg_test_cmake(PACKAGE_NAME ${PORT})
