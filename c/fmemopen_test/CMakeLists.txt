cmake_minimum_required(VERSION 3.8)

project(fmemopen_test C)

if (WIN32)
    add_library(fmemopen ${CMAKE_CURRENT_LIST_DIR}/../fmemopen.c)
    target_compile_definitions(fmemopen
        PRIVATE
            $<$<BOOL:${MSVC}>:_CRT_SECURE_NO_WARNINGS>
            $<$<BOOL:${MSVC}>:_CRT_NONSTDC_NO_DEPRECATE>
    )

    add_library(fmemopen_tmpfile ${CMAKE_CURRENT_LIST_DIR}/../fmemopen.c)
    target_compile_definitions(fmemopen_tmpfile
        PRIVATE
            $<$<BOOL:${MSVC}>:_CRT_SECURE_NO_WARNINGS>
            $<$<BOOL:${MSVC}>:_CRT_NONSTDC_NO_DEPRECATE>
            USE_STDC_TMPFILE
    )

    add_executable(fmemopen_v1_test fmemopen_test.c)
    target_compile_definitions(fmemopen_v1_test PRIVATE fmemopen=fmemopen_v1)
    target_link_libraries(fmemopen_v1_test PRIVATE fmemopen shlwapi)

    add_executable(fmemopen_v2_test fmemopen_test.c)
    target_compile_definitions(fmemopen_v2_test PRIVATE fmemopen=fmemopen_v2)
    target_link_libraries(fmemopen_v2_test PRIVATE fmemopen shlwapi)

    add_executable(fmemopen_v2_tmpfile_test fmemopen_test.c)
    target_compile_definitions(fmemopen_v2_tmpfile_test PRIVATE fmemopen=fmemopen_v2)
    target_link_libraries(fmemopen_v2_tmpfile_test PRIVATE fmemopen_tmpfile shlwapi)
else ()
    add_executable(fmemopen_test fmemopen_test.c)
endif ()
