cmake_minimum_required(VERSION 3.9)

project(kcp_test C CXX)

find_package(kcp CONFIG REQUIRED)

set(tests
    test_opendialog
    test_opendialogmultiple
    test_pickfolder
    test_savedialog
)

file(DOWNLOAD
    "https://raw.githubusercontent.com/skywind3000/kcp/master/test.h"
    "${CMAKE_CURRENT_BINARY_DIR}/test.h"
)

file(DOWNLOAD
    "https://raw.githubusercontent.com/skywind3000/kcp/master/test.cpp"
    "${CMAKE_CURRENT_BINARY_DIR}/test.cpp"
)

add_executable(kcp_test "${CMAKE_CURRENT_BINARY_DIR}/test.cpp")
target_link_libraries(kcp_test PRIVATE kcp::kcp)
