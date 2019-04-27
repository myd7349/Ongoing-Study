cmake_minimum_required(VERSION 3.8)

project(jsmn_tests C)

foreach(source test.h tests.c testutil.h)
    file(DOWNLOAD
        "https://raw.githubusercontent.com/zserge/jsmn/master/test/${source}"
        "${CMAKE_CURRENT_BINARY_DIR}/${source}"
    )
endforeach()

find_path(
    JSMN_INCLUDE_DIR
    NAMES jsmn.h
)

file(READ ${CMAKE_CURRENT_BINARY_DIR}/testutil.h _contents)
string(REPLACE "#include \"../jsmn.h\"" "#include <jsmn.h>" _contents "${_contents}")
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/testutil.h "${_contents}")

add_executable(jsmn_tests ${CMAKE_CURRENT_BINARY_DIR}/tests.c)
target_include_directories(jsmn_tests PRIVATE ${JSMN_INCLUDE_DIR})
