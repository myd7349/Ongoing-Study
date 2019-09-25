include(vcpkg_common_functions)

vcpkg_check_linkage(ONLY_STATIC_LIBRARY)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO protocolbuffers/upb
    REF 26245628a9b8abfc217b080eec73af477a5fc65c
    SHA512 d8374e4f077d41eb345ced9e7391e1786ad5e4961b15c6ae408999ef441730365ac0bfa6115340ccc79e7746d2d15b6f1865ede874f47cdf41c1b63eb92a83e1
    HEAD_REF master
    PATCHES
        fix-msvc.patch
)

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    PREFER_NINJA
)

vcpkg_build_cmake()

#vcpkg_copy_pdbs()

#vcpkg_fixup_cmake_targets(CONFIG_PATH lib/cmake/docopt)

#file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/include)

# Handle copyright
configure_file(${SOURCE_PATH}/LICENSE ${CURRENT_PACKAGES_DIR}/share/${PORT}/copyright COPYONLY)
