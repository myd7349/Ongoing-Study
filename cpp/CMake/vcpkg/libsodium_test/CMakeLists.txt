cmake_minimum_required(VERSION 3.9)

project(libsodium_test)

include(CTest)

configure_file(
    ${CMAKE_CURRENT_LIST_DIR}/DownloadSodium.cmake.in
    ${CMAKE_CURRENT_LIST_DIR}/libsodium_download/CMakeLists.txt
)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/libsodium_download
)

execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/libsodium_download
)

file(STRINGS ${CMAKE_CURRENT_LIST_DIR}/libsodium/configure.ac config_ac_contents)

foreach (line ${config_ac_contents})
    if (line MATCHES "AC_INIT\\(\\[libsodium\\],\\[([0-9.]+)\\],")
        set(VERSION ${CMAKE_MATCH_1})
    elseif (line MATCHES "SODIUM_LIBRARY_VERSION_(MAJOR|MINOR)=([0-9]+)")
        set(SODIUM_LIBRARY_VERSION_${CMAKE_MATCH_1} ${CMAKE_MATCH_2})
    endif ()
endforeach ()

message("VERSION: ${VERSION}")
message("SODIUM_LIBRARY_VERSION_MAJOR: ${SODIUM_LIBRARY_VERSION_MAJOR}")
message("SODIUM_LIBRARY_VERSION_MINOR: ${SODIUM_LIBRARY_VERSION_MINOR}")

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_LIST_DIR}/libsodium/contrib
)


find_package(sodium QUIET)

message(STATUS "sodium_FOUND: ${sodium_FOUND}")
message(STATUS "sodium_VERSION: ${sodium_VERSION}")
message(STATUS "sodium_INCLUDE_DIR: ${sodium_INCLUDE_DIR}")
message(STATUS "sodium_LIBRARY_DEBUG: ${sodium_LIBRARY_DEBUG}")
message(STATUS "sodium_LIBRARY_RELEASE: ${sodium_LIBRARY_RELEASE}")
message(STATUS "sodium_DLL_DEBUG: ${sodium_DLL_DEBUG}")
message(STATUS "sodium_DLL_RELEASE: ${sodium_DLL_RELEASE}")

find_package(unofficial-sodium CONFIG REQUIRED)

message(STATUS "sodium_FOUND: ${sodium_FOUND}")
message(STATUS "sodium_VERSION: ${sodium_VERSION}")
message(STATUS "sodium_INCLUDE_DIR: ${sodium_INCLUDE_DIR}")
message(STATUS "sodium_LIBRARY_DEBUG: ${sodium_LIBRARY_DEBUG}")
message(STATUS "sodium_LIBRARY_RELEASE: ${sodium_LIBRARY_RELEASE}")
message(STATUS "sodium_LIBRARIES: ${sodium_LIBRARIES}")
message(STATUS "sodium_DLL_DEBUG: ${sodium_DLL_DEBUG}")
message(STATUS "sodium_DLL_RELEASE: ${sodium_DLL_RELEASE}")

if (NOT VERSION STREQUAL sodium_VERSION)
    message(FATAL_ERROR "libsodium versions mismatch.")
endif ()

file(GLOB test_sources ${CMAKE_CURRENT_LIST_DIR}/libsodium/test/default/*.c)

set(BANG ON)

foreach (test_src ${test_sources})
    get_filename_component(test_name ${test_src} NAME_WE)

    add_executable(${test_name} ${test_src})
    
    if (MSVC)
        target_compile_definitions(${test_name} PRIVATE _CRT_SECURE_NO_WARNINGS)
    endif ()

    if (BANG)
        target_include_directories(${test_name} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/libsodium/test/quirks)
        target_link_libraries(${test_name} PRIVATE unofficial-sodium::sodium)
        set(BANG OFF)
    else ()
        target_include_directories(
            ${test_name}
            PRIVATE
                ${sodium_INCLUDE_DIR}
                ${CMAKE_CURRENT_LIST_DIR}/libsodium/test/quirks
        )
        target_link_libraries(${test_name} PRIVATE ${sodium_LIBRARIES})
        set(BANG ON)
    endif ()

    add_custom_command(TARGET ${test_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_LIST_DIR}/libsodium/test/default/${test_name}.exp"
        $<TARGET_FILE_DIR:${test_name}>)

    add_test(
        NAME ${test_name}
        COMMAND ${test_name}
        WORKING_DIRECTORY $<TARGET_FILE_DIR:${test_name}>
    )
endforeach ()


# References:
# https://stackoverflow.com/questions/50468620/what-does-enable-testing-do-in-cmake
