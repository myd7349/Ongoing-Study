cmake_minimum_required(VERSION 3.8)

project(attribute-demo LANGUAGES C CXX)

find_package(fmt CONFIG REQUIRED)
set(HIGHFIVE_USE_BOOST OFF CACHE BOOL "Enable Boost Support" FORCE)
find_package(HighFive CONFIG REQUIRED)

if(MSVC)
    option(MSVC_STATIC_RUNTIME "Use MSVC static runtime" OFF)

    # https://gitlab.kitware.com/cmake/community/wikis/FAQ#how-can-i-build-my-msvc-application-with-a-static-runtime
    # https://github.com/kkos/oniguruma/blob/c0881d81467216ecdfa1452c54271e7f60c8e4a5/CMakeLists.txt#L74-L81
    if(MSVC_STATIC_RUNTIME)
        foreach(flag_var
            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
            if(${flag_var} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
            endif(${flag_var} MATCHES "/MD")
        endforeach()
    endif()
endif()

add_executable(attribute-demo attribute-demo.cpp)
target_compile_definitions(attribute-demo PRIVATE $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>)
target_compile_options(attribute-demo PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>)
target_link_libraries(attribute-demo PRIVATE fmt::fmt HighFive)
target_compile_features(attribute-demo PRIVATE cxx_std_11)

if(WIN32)
    add_library(wconv "${CMAKE_CURRENT_LIST_DIR}/../../../../c/Win32/wconv.c")
    target_include_directories(wconv PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../../../../c/Win32")

    target_compile_definitions(attribute-demo PRIVATE WCONV_AVAILABLE)
    target_link_libraries(attribute-demo PRIVATE wconv)
endif()

# References:
# [How do I activate C++ 11 in CMake?](https://stackoverflow.com/questions/10851247/how-do-i-activate-c-11-in-cmake)
# [Take control of your vcpkg dependencies with versioning support](https://devblogs.microsoft.com/cppblog/take-control-of-your-vcpkg-dependencies-with-versioning-support/)
# [cmake set subdirectory options](https://stackoverflow.com/questions/20239334/cmake-set-subdirectory-options/20239564)
