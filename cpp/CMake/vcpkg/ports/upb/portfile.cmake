include(vcpkg_common_functions)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO google/upb
    REF 9bb0814c48cb4d4df87ca64c9fabba5d15183cc1
    SHA512 2e23e64224e9984269d4bce477201dc34420fe00bc504dcea5de81f2e35f06e1b6fa97b7f6e739b854f0e0bc49156b59cfd613b95b0e0016c829163877887708
    HEAD_REF master
)

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    PREFER_NINJA
)

vcpkg_install_cmake()

#vcpkg_fixup_cmake_targets(CONFIG_PATH lib/cmake/docopt)

#file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/include)

# Handle copyright
#file(INSTALL
#    ${SOURCE_PATH}/LICENSE-MIT
#    DESTINATION ${CURRENT_PACKAGES_DIR}/share/docopt RENAME copyright)
#configure_file(${SOURCE_PATH}/LICENSE ${CURRENT_PACKAGES_DIR}/share/double-conversion/copyright COPYONLY)

vcpkg_copy_pdbs()
