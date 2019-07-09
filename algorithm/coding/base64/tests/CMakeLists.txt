add_library(dump dump.c)

add_executable(base64_tests base64_tests.c)
target_link_libraries(base64_tests PRIVATE base64 dump)
add_test(base64_tests base64_tests)

if (WIN32)
    add_library(wconv wconv.c)

    add_executable(char_tests wchar_tests.c)
    target_compile_options(char_tests PRIVATE "/source-charset:utf-8")
    target_link_libraries(char_tests PRIVATE base64 dump)

    add_executable(wchar_tests wchar_tests.c)
    target_compile_definitions(wchar_tests PRIVATE UNICODE _UNICODE)
    target_compile_options(wchar_tests PRIVATE "/source-charset:utf-8")
    target_link_libraries(wchar_tests PRIVATE base64 wconv dump)
endif ()
