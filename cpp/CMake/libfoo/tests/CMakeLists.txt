if (NOT TARGET foo AND NOT TARGET foo_static)
    cmake_minimum_required(VERSION 3.8)
    project(foo_tests C)

    find_package(foo CONFIG REQUIRED)
endif ()


add_executable(foo_test "foo_test.c")

if (TARGET foo)
    target_link_libraries(foo_test PRIVATE foo)
elseif (TARGET foo_static)
    target_link_libraries(foo_test PRIVATE foo_static)
endif ()

add_test(NAME foo_test COMMAND foo_test)
