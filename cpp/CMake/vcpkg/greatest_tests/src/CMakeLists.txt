include(CTest)

find_path(
    GREATEST_INCLUDE_DIR
    NAMES greatest.h
)

set(root_url "https://raw.githubusercontent.com/silentbicycle/greatest/master/")

set(tests
    example_cpp.cpp
    example_no_runner.c
    example_no_suite.c
    example_trunc.c
)

if (UNIX)
    list(APPEND tests
        example.c
        example_shuffle.c
        example_suite.c 
    )
endif (UNIX)

foreach (test_src_file ${tests})
    file(DOWNLOAD
        "${root_url}${test_src_file}"
        "${CMAKE_BINARY_DIR}/${test_src_file}"
    )

    get_filename_component(test_name ${test_src_file} NAME_WE)

    add_executable(${test_name} "${CMAKE_BINARY_DIR}/${test_src_file}")

    target_include_directories(
        ${test_name}
        PRIVATE
            ${GREATEST_INCLUDE_DIR}
    )

    add_test(${test_name} ${test_name})
endforeach ()
