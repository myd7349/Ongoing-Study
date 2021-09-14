cmake_minimum_required(VERSION 3.8)

project(wchar_t_test LANGUAGES CXX)

find_package(glog CONFIG REQUIRED)

function(create_target target)
    add_executable(${target} wchar_t_test.cpp)
    if(MSVC AND MSVC_VERSION GREATER_EQUAL 1900)
        target_compile_options(${target} PRIVATE /source-charset:utf-8)
    endif()
    target_link_libraries(${target} PRIVATE glog::glog)
endfunction()

create_target(wchar_t_test)

if(WIN32)
    enable_language(C)

    set(wconv_root_dir "${CMAKE_CURRENT_LIST_DIR}/../../../../c/Win32")
    add_library(wconv STATIC "${wconv_root_dir}/wconv.c")
    target_include_directories(wconv PUBLIC "${wconv_root_dir}")
endif()

if(WIN32)
    create_target(wchar_t_test_wconv)
    target_compile_definitions(wchar_t_test_wconv PRIVATE WCONV_SUPPORT)
    target_link_libraries(wchar_t_test_wconv PRIVATE wconv)
endif()

create_target(wchar_t_test_wchar_logging)
target_compile_definitions(
    wchar_t_test_wchar_logging
    PRIVATE
        WCHAR_LOGGING_SUPPORT
        $<$<CXX_COMPILER_ID:MSVC>:
            _CRT_SECURE_NO_WARNINGS
        >
)

create_target(wchar_t_test_wchar_logging_setlocale)
target_compile_definitions(
    wchar_t_test_wchar_logging_setlocale
    PRIVATE
        WCHAR_LOGGING_SUPPORT
        SET_LOCALE
        $<$<CXX_COMPILER_ID:MSVC>:
            _CRT_SECURE_NO_WARNINGS
        >
)

if(WIN32)
    create_target(wchar_t_test_wchar_logging_setlocale_wconv)
    target_compile_definitions(
        wchar_t_test_wchar_logging_setlocale_wconv
        PRIVATE
            WCHAR_LOGGING_SUPPORT
            SET_LOCALE
            WCONV_SUPPORT
            $<$<CXX_COMPILER_ID:MSVC>:
                _CRT_SECURE_NO_WARNINGS
            >
    )
    target_link_libraries(wchar_t_test_wchar_logging_setlocale_wconv PRIVATE wconv)
endif()
