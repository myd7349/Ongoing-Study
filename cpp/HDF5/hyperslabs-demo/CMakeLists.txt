cmake_minimum_required(VERSION 3.8)

project(hyperslabs-demo LANGUAGES C CXX)

find_package(hdf5 CONFIG REQUIRED)

add_executable(hyperslabs-demo-c hyperslabs-demo.c)
target_link_libraries(hyperslabs-demo-c PRIVATE hdf5::hdf5-shared)

if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/h5_extend_write.c")
    file(DOWNLOAD
        "https://raw.githubusercontent.com/HDFGroup/hdf5/develop/examples/h5_extend_write.c"
        "${CMAKE_CURRENT_BINARY_DIR}/h5_extend_write.c")

    add_executable(h5_extend_write h5_extend_write.c)
    target_link_libraries(h5_extend_write PRIVATE hdf5::hdf5-shared)
endif()

set(examples_root_url "https://raw.githubusercontent.com/HDFGroup/hdf5/1.12/master/c%2B%2B/examples/")
set(examples h5tutr_extend.cpp extend_ds.cpp)

foreach(example IN LISTS examples)
    if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/${example}")
        file(DOWNLOAD
            "${examples_root_url}${example}"
            "${CMAKE_CURRENT_BINARY_DIR}/${example}"
        )
    endif()
    
    get_filename_component(example_title ${example} NAME_WE)

    add_executable(${example_title} "${CMAKE_CURRENT_BINARY_DIR}/${example}")
    target_link_libraries(${example_title} PRIVATE hdf5::hdf5_cpp-shared)
endforeach()

add_executable(hyperslabs-demo hyperslabs-demo.cpp)
target_link_libraries(hyperslabs-demo PRIVATE hdf5::hdf5_cpp-shared)
target_compile_features(hyperslabs-demo PRIVATE cxx_std_11)

# References:
# [How do I activate C++ 11 in CMake?](https://stackoverflow.com/questions/10851247/how-do-i-activate-c-11-in-cmake)
