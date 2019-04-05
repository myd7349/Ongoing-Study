cmake_minimum_required(VERSION 3.8)

project(find_git)

find_package(Git QUIET)
if (Git_FOUND)
    message(STATUS "GIT_EXECUTABLE: ${GIT_EXECUTABLE}")

    if (CMAKE_HOST_SYSTEM_NAME MATCHES "^Windows")
        # cmd /c "E:/Program Files/Git/cmd/git.exe" rev-list --branches HEAD | find /v " " /c
        # cmd /c ""E:/Program Files/Git/cmd/git.exe" rev-list --branches HEAD | find /v " " /c"
        execute_process(
            COMMAND ${GIT_EXECUTABLE} rev-list --branches HEAD
            OUTPUT_VARIABLE REV_LIST_STR
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            ENCODING AUTO
        )
        string(REPLACE "\n" ";" REV_LIST ${REV_LIST_STR})
        list(LENGTH REV_LIST REV_LIST_LEN)
        math(EXPR GIT_VERSION "${REV_LIST_LEN} - 1")
    else ()
        execute_process(
            COMMAND bash "-c" "${GIT_EXECUTABLE} rev-list --branches HEAD | wc -l | tr -d ' ' | tr -d '\n'"
            OUTPUT_VARIABLE GIT_VERSION
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
    endif ()

    message(STATUS "GIT_VERSION: ${GIT_VERSION}")
endif ()

find_program(GIT_PATH git)
if (GIT_PATH MATCHES "git(.exe)*$")
    message(STATUS "GIT_PATH: ${GIT_PATH}")
endif ()

# References:
# https://github.com/nanomsg/nanomsg/blob/master/CMakeLists.txt#L67
# https://github.com/KjellKod/g3log/blob/master/CMakeLists.txt#L82
# https://ss64.com/nt/syntax-esc.html
# https://stackoverflow.com/questions/34905194/cmake-how-to-call-execute-process-with-a-double-quote-in-the-argument-a-k-a-u
# https://stackoverflow.com/questions/34763847/add-quotation-mark-in-cmake-string
# https://stackoverflow.com/questions/9267278/using-the-dos-start-command-when-passed-arguments-have-quotes
# https://stackoverflow.com/questions/355988/how-do-i-deal-with-quote-characters-when-using-cmd-exe
# https://stackoverflow.com/questions/5272781/what-is-common-way-to-split-string-into-list-with-cmake
