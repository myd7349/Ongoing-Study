cmake_minimum_required(VERSION 3.9)

project(glui_examples C CXX)

find_package(SymEngine CONFIG REQUIRED)
find_path(SYMENGINE_INCLUDE_DIR symengine/expression.h)

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

add_executable(symengine_test symengine_test.cpp)
target_include_directories(symengine_test PRIVATE ${SYMENGINE_INCLUDE_DIR})
target_link_libraries(symengine_test PRIVATE symengine)
