if (NOT TARGET foo AND NOT TARGET foo_static)
    cmake_minimum_required(VERSION 3.8)
    project(foo_tests C)

    find_package(foo CONFIG REQUIRED)

    set(foo_TARGET foo::foo)
    set(foo_static_TARGET foo::foo_static)

    include(CTest)
else ()
    set(foo_TARGET foo)
    set(foo_static_TARGET foo_static)
endif ()

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")

add_executable(foo_test "foo_test.c")

if (TARGET ${foo_TARGET})
    target_link_libraries(foo_test PRIVATE ${foo_TARGET})
    add_custom_command(
        TARGET foo_test
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${foo_TARGET}> $<TARGET_FILE_DIR:foo_test>)
elseif (TARGET ${foo_static_TARGET})
    target_link_libraries(foo_test PRIVATE ${foo_static_TARGET})
endif ()

add_test(NAME foo_test COMMAND foo_test)
