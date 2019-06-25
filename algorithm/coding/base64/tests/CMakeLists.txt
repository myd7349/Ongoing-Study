add_executable(base64_tests base64_tests.c)
target_link_libraries(base64_tests base64)
add_test(base64_tests base64_tests)
