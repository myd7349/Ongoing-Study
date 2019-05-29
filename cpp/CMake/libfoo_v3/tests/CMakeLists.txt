cmake_minimum_required(VERSION 3.8)
project(foo_tests C)

include(CTest)

if (NOT TARGET libfoo AND NOT TARGET libfoo_static)
    find_package(foo CONFIG REQUIRED)

    set(libfoo_TARGET foo::libfoo)
    set(libfoo_static_TARGET foo::libfoo_static)
else ()
    set(libfoo_TARGET libfoo)
    set(libfoo_static_TARGET libfoo_static)
endif ()

if (BUILD_TESTING)
    add_executable(foo_test "foo_test.c")
    
    if (TARGET ${libfoo_TARGET})
        target_link_libraries(foo_test PRIVATE ${libfoo_TARGET})
        add_custom_command(
            TARGET foo_test
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${libfoo_TARGET}>     $<TARGET_FILE_DIR:foo_test>)
    elseif (TARGET ${libfoo_static_TARGET})
        target_link_libraries(foo_test PRIVATE ${libfoo_static_TARGET})
    endif ()
    
    add_test(NAME foo_test COMMAND foo_test)
endif ()
