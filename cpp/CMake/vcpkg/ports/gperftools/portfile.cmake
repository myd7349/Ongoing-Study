include(vcpkg_common_functions)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO gperftools/gperftools
    REF fe62a0baab87ba3abca12f4a621532bf67c9a7d2
    SHA512 fc0fb2c56d38046ac7bc2d36863dabf073b7aede7ce18916228d7b9f64cf33ae754708bff028353ada52bf4b79a7cd3e3334c1558a9ba64b06326b1537faf690
    HEAD_REF master
)

file(COPY ${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt DESTINATION ${SOURCE_PATH})

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    PREFER_NINJA
    DISABLE_PARALLEL_CONFIGURE
    OPTIONS
        -DGPERFTOOLS_BUILD_TOOLS=OFF
)

vcpkg_install_cmake()

vcpkg_copy_pdbs()

#vcpkg_fixup_cmake_targets(CONFIG_PATH CMake)

file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/include)

# Handle copyright
configure_file(${SOURCE_PATH}/COPYING ${CURRENT_PACKAGES_DIR}/share/${PORT}/copyright COPYONLY)

# CMake integration test
#vcpkg_test_cmake(PACKAGE_NAME ${PORT})
