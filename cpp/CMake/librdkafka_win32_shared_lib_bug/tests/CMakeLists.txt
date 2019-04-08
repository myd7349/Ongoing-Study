if (NOT TARGET foo)
    cmake_minimum_required(VERSION 3.8)
    project(foo_test CXX)

    find_package(foo CONFIG REQUIRED)
endif ()

foreach (test_name hello_test rd_export_test static_const_member_test version_test)
    add_executable(${test_name} ${test_name}.cpp)
    target_link_libraries(${test_name} PRIVATE foo)
    add_test(NAME ${test_name} COMMAND ${test_name})
    add_custom_command(
        TARGET ${test_name}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:foo> $<TARGET_FILE_DIR:${test_name}>)
endforeach ()
