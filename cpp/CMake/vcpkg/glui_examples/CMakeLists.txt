cmake_minimum_required(VERSION 3.9)

project(glui_examples C CXX)

find_package(glui CONFIG REQUIRED)

option(USING_MSVC_STATIC_RUNTIME "Using MSVC static runtime" OFF)

if(MSVC AND USING_MSVC_STATIC_RUNTIME)
    foreach(flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        if(${flag_var} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endif(${flag_var} MATCHES "/MD")
    endforeach()
endif()

set(url "https://raw.githubusercontent.com/libglui/glui/093edc777c02118282910bdee59f8db1bd46a84d/example/")

set(examples
    example1
    example2
    example3
    example4
    example5
    example6
)

foreach (example ${examples})
    if (NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/${example}.cpp")
        file(DOWNLOAD
            "${url}${example}.cpp"
            "${CMAKE_CURRENT_BINARY_DIR}/${example}.cpp"
        )
    endif ()

    add_executable(${example} "${CMAKE_CURRENT_BINARY_DIR}/${example}.cpp")
    target_link_libraries(${example} PRIVATE glui::glui glui::glui_static)
endforeach ()
