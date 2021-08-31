cmake_minimum_required(VERSION 3.8)

project(kfr_examples LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

find_package(kfr REQUIRED)

set(examples_root_url "https://raw.githubusercontent.com/kfrlib/kfr/4.2.1/examples/")
set(examples
    biquads.cpp
    #ccv.cpp
    #dft.cpp
    fir.cpp
    iir.cpp
    sample_rate_conversion.cpp
    window.cpp	
)

foreach(example IN LISTS examples)
    if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/${example}")
        file(DOWNLOAD "${examples_root_url}${example}" "${CMAKE_CURRENT_BINARY_DIR}/${example}")
    endif()

    get_filename_component(example_title ${example} NAME_WE)

    add_executable("${example_title}" "${CMAKE_CURRENT_BINARY_DIR}/${example}")
	target_include_directories("${example_title}" PRIVATE ${kfr_INCLUDE_DIR})
    target_link_libraries("${example_title}" PRIVATE ${kfr_io_LIBRARIES})
    target_compile_features("${example_title}" PRIVATE cxx_std_17)
endforeach()
