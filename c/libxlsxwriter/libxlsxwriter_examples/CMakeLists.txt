cmake_minimum_required(VERSION 3.9)

project(libxlsxwriter_examples C)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")

find_package(libxlsxwriter REQUIRED)

message(STATUS "LIBXLSXWRITER_INCLUDE_DIRS: ${LIBXLSXWRITER_INCLUDE_DIRS}")
message(STATUS "LIBXLSXWRITER_LIBRARIES: ${LIBXLSXWRITER_LIBRARIES}")
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

add_executable(example01 example01.c)
target_include_directories(example01 PRIVATE ${LIBXLSXWRITER_INCLUDE_DIRS})
target_link_libraries(example01 PRIVATE ${LIBXLSXWRITER_LIBRARIES})

if (WIN32)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        get_filename_component(xlswriter_dll_dir "${LIBXLSXWRITER_LIBRARY_DEBUG}" DIRECTORY)
    else ()
        get_filename_component(xlswriter_dll_dir "${LIBXLSXWRITER_LIBRARY_RELEASE}" DIRECTORY)
    endif ()
    get_filename_component(xlswriter_dll_dir "${xlswriter_dll_dir}" DIRECTORY)

    foreach (dll_name xlsxwriter)
        if (EXISTS "${xlswriter_dll_dir}/bin/${dll_name}.dll")
            add_custom_command(
                TARGET example01
                POST_BUILD
                COMMAND "${CMAKE_COMMAND}"
                ARGS
                    -E
                    copy_if_different
                    "${xlswriter_dll_dir}/bin/${dll_name}.dll"
                    $<TARGET_FILE_DIR:example01>
                VERBATIM
            )
        endif ()
    endforeach ()
endif ()
