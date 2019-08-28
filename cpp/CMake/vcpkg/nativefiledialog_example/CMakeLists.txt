cmake_minimum_required(VERSION 3.9)

project(nativefiledialog_example C CXX)

find_package(unofficial-nativefiledialog CONFIG REQUIRED)

set(tests
    test_opendialog
    test_opendialogmultiple
    test_pickfolder
    test_savedialog
)

foreach (test_name ${tests})
    if (NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/${test_name}.c")
        file(DOWNLOAD
            "https://raw.githubusercontent.com/mlabbe/nativefiledialog/master/test/${test_name}.c"
            "${CMAKE_CURRENT_BINARY_DIR}/${test_name}.c"
        )
    endif ()

    add_executable(${test_name} "${CMAKE_CURRENT_BINARY_DIR}/${test_name}.c")
    target_link_libraries(${test_name} PRIVATE unofficial::nativefiledialog::nfd)
endforeach ()
