add_library(dump dump.c)

add_executable(base64_tests base64_tests.c)
target_link_libraries(base64_tests PRIVATE base64 dump)
add_test(base64_tests base64_tests)

add_executable(base64_tests_cpp base64_tests.cpp)
target_link_libraries(base64_tests_cpp PRIVATE base64 dump)
add_test(base64_tests_cpp base64_tests_cpp)

if (WIN32)
    add_library(wconv "${CMAKE_CURRENT_LIST_DIR}/../../../../c/Win32/wconv.c")
    target_include_directories(wconv PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../../../../c/Win32")

    add_executable(char_tests wchar_tests.c)
    target_compile_options(char_tests PRIVATE "/source-charset:utf-8")
    target_link_libraries(char_tests PRIVATE base64 wconv dump)

    add_executable(wchar_tests wchar_tests.c)
    target_compile_definitions(wchar_tests PRIVATE UNICODE _UNICODE)
    target_compile_options(wchar_tests PRIVATE "/source-charset:utf-8")
    target_link_libraries(wchar_tests PRIVATE base64 wconv dump)
endif ()
