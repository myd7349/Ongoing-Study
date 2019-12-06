cmake_minimum_required(VERSION 3.8)

project(list_dir_test C)

function (scan_directory)
    set(options FULL_PATH FILE DIRECTORY RECURSIVE)
    set(one_value_args ROOT_PATH OUTPUT_VARIABLE)
    set(multi_value_keywords GLOB_PATTERNS)

    cmake_parse_arguments(sd_ "${options}" "${one_value_args}" "${multi_value_keywords}")

    if (NOT DEFINED sd_ROOT_PATH)
        message(FATAL_ERROR "Missing ROOT_PATH: ${sd_ROOT_PATH}")
    endif ()

    if (NOT DEFINED sd_OUTPUT_VARIABLE)
        message(FATAL_ERROR "Missing OUTPUT_VARIABLE.")
    endif ()

    set(file_args)
    if (sd_RECURSIVE)
        list(APPEND file_args GLOB_RECURSE sub_entries)
    else ()
        list(APPEND file_args GLOB sub_entries)
    endif ()

    list(APPEND file_args LIST_DIRECTORIES ${sd_DIRECTORY})

    if (NOT DEFINED sd_FULL_PATH)
        list(APPEND file_args RELATIVE ${sd_ROOT_PATH})
    endif ()

    set(patterns)
    foreach (pattern ${sd_GLOB_PATTERNS})
        list(APPEND patterns "${sd_ROOT_PATH}/${pattern}")
    endforeach ()

    list(LENGTH patterns patterns_length)
    if (patterns_length EQUAL 0)
        list(APPEND patterns "${sd_ROOT_PATH}/*")
    endif ()

    list(APPEND file_args ${patterns})

    file(${file_arg})

    set(dirlist "")

    foreach (entry ${sub_entries})
        message(STATUS "${entry}")
        if (IS_DIRECTORY ${curdir}/${child})
            list(APPEND dirlist ${child})
        endif ()
    endforeach ()

    set(${result} ${dirlist})
endfunction ()

scan_directory(
    ROOT_PATH ${CMAKE_CURRENT_LIST_DIR}
    OUTPUT_VARIABLE items
)

# References:
# https://stackoverflow.com/questions/7787823/cmake-how-to-get-the-name-of-all-subdirectories-of-a-directory
# https://stackoverflow.com/questions/27302142/cmake-detect-empty-directory-during-build-time
# https://stackoverflow.com/questions/50738181/cmake-glob-list-of-files-without-directory-path
