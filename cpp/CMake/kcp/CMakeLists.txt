CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)

if(DEFINED PROJECT_NAME)
    set(KCP_IS_SUBPROJECT ON)
else()
    set(KCP_IS_SUBPROJECT OFF)
endif()

project(kcp LANGUAGES C)

include(CMakeDependentOption)
include(CTest)
include(GNUInstallDirs)

cmake_dependent_option(KCP_BUILD_SHARED_LIBS "Build KCP shared lib" OFF "BUILD_SHARED_LIBS" ON)
cmake_dependent_option(KCP_BUILD_INSTALL "Build install target" ON "BUILD_TESTING;NOT KCP_IS_SUBPROJECT" OFF)
cmake_dependent_option(KCP_BUILD_TESTS "Build tests" ON "BUILD_TESTING;NOT KCP_IS_SUBPROJECT" OFF)

message("KCP_IS_SUBPROJECT: ${KCP_IS_SUBPROJECT}")
message("BUILD_SHARED_LIBS: ${BUILD_SHARED_LIBS}")
message("KCP_BUILD_SHARED_LIBS: ${KCP_BUILD_SHARED_LIBS}")
message("KCP_BUILD_INSTALL: ${KCP_BUILD_INSTALL}")
message("KCP_BUILD_TESTS: ${KCP_BUILD_TESTS}")

if(KCP_BUILD_SHARED_LIBS)
    set(exports_def_file "${CMAKE_CURRENT_BINARY_DIR}/exports.def")
    set(exports_def_contents
"EXPORTS 
    ikcp_create
    ikcp_release
    ikcp_setoutput
    ikcp_recv
    ikcp_send
    ikcp_update
    ikcp_check
    ikcp_input
    ikcp_flush
    ikcp_peeksize
    ikcp_setmtu
    ikcp_wndsize
    ikcp_waitsnd
    ikcp_nodelay
    ikcp_log
    ikcp_allocator
    ikcp_getconv
")

    if(WIN32)
        file(WRITE "${exports_def_file}" "${exports_def_contents}")
        add_library(kcp SHARED ikcp.c "${exports_def_file}")
    else()
        add_library(kcp SHARED ikcp.c)
    endif()
else()
    add_library(kcp STATIC ikcp.c)
endif()

if(KCP_BUILD_INSTALL)
    install(FILES ikcp.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    install(TARGETS kcp
        EXPORT kcp-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    install(EXPORT kcp-targets
        FILE kcp-config.cmake
        NAMESPACE kcp::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kcp
    )
endif()

if(KCP_BUILD_TESTS)
    enable_language(CXX)
    
    add_executable(kcp_test test.cpp)
    if(MSVC AND NOT (MSVC_VERSION LESS 1900))
        target_compile_options(kcp_test PRIVATE /utf-8)
    endif()
endif()

# References:
# [Is it possible to get CMake to build both a static and shared library at the same time?](https://stackoverflow.com/questions/2152077/is-it-possible-to-get-cmake-to-build-both-a-static-and-shared-library-at-the-sam)
# [How to use variables and avoid CMP0054 policy violations?](https://stackoverflow.com/questions/45900159/how-to-use-variables-and-avoid-cmp0054-policy-violations)
