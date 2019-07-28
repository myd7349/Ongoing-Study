cmake_minimum_required(VERSION 3.8)

project(parse_arguments_test C)

function(install_tools)
    cmake_parse_arguments(_vct "" "SEARCH_DIR" "TOOL_NAMES" ${ARGN})

    message(STATUS "----------------------------------")
    message(STATUS "SEARCH_DIR: ${_vct_SEARCH_DIR}")
    message(STATUS "TOOL_NAMES: ${_vct_TOOL_NAMES}")
    message(STATUS "ARGN: ${ARGN}")
endfunction()

install_tools(a b c)
install_tools(x SEARCH_DIR tooldir a b c)
install_tools(x tooldir TOOL_NAMES a b c)
install_tools(SEARCH_DIR tooldir TOOL_NAMES a b c)
install_tools(x SEARCH_DIR tooldir TOOL_NAMES a b c)
