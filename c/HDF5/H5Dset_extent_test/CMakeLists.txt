cmake_minimum_required(VERSION 3.8)

project(H5Dset_extent_test LANGUAGES C)

find_package(hdf5 CONFIG REQUIRED)

add_executable(H5Dset_extent_test H5Dset_extent_test.c)
target_link_libraries(H5Dset_extent_test PRIVATE hdf5::hdf5-shared)
