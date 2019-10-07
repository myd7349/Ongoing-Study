cmake_minimum_required(VERSION 3.9)

project(wepoll_tests C)

include(FetchContent)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

find_package(wepoll REQUIRED)
    
FetchContent_Declare(
    wepoll
    GIT_REPOSITORY https://github.com/piscisaureus/wepoll
    GIT_TAG        d5f8f5f1b1be1a4ba8adb51eb4ee4de7a305a9c8
)

FetchContent_GetProperties(wepoll)
if (NOT wepoll_POPULATED)
    FetchContent_Populate(wepoll)
endif ()

set(shared_sources
    shared/leak-check.c
    shared/test-util.c
    shared/test-util.h
)

set(tests_shared_sources)

foreach (source ${shared_sources})
    if (NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/test/${source}")
        file(DOWNLOAD
            "https://raw.githubusercontent.com/piscisaureus/wepoll/master/test/${source}"
            "${CMAKE_CURRENT_BINARY_DIR}/test/${source}.c"
        )
    endif ()

    list(APPEND tests_shared_sources "${CMAKE_CURRENT_BINARY_DIR}/test/${source}")
endforeach ()

set(tests
    test-auto-drop-on-close
    test-connect-fail-events
    test-connect-success-events
    test-ctl-fuzz
    test-error
    test-leak-1
    test-mixed-socket-types
    test-multi-poll
    test-oneshot-and-hangup
    test-reflock
    test-tree
    test-udp-pings
)

foreach (test_name ${tests})
    add_executable(
        ${test_name}
        "${wepoll_SOURCE_DIR}/src/error.c"
        "${wepoll_SOURCE_DIR}/src/ws.c"
        "${wepoll_SOURCE_DIR}/test/${test_name}.c"
        "${wepoll_SOURCE_DIR}/test/shared/leak-check.c"
        "${wepoll_SOURCE_DIR}/test/shared/test-util.c"
    )

    target_compile_definitions(
        ${test_name}
        PRIVATE
        WEPOLL_INTERNAL
    )

    target_include_directories(
        ${test_name}
        PRIVATE
            "${WEPOLL_INCLUDE_DIRS}"
            "${wepoll_SOURCE_DIR}/src"
            "${wepoll_SOURCE_DIR}/src/combined"
            "${wepoll_SOURCE_DIR}/test/shared"
    )

    target_link_libraries(
        ${test_name}
        PRIVATE
            ${WEPOLL_LIBRARIES}
            Ws2_32
    )
endforeach ()
