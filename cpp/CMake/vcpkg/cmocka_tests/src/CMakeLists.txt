find_package(cmocka CONFIG REQUIRED)
find_package(roaring CONFIG REQUIRED)

include(CTest)

message(STATUS "CMOCKA_LIBRARIES: ${CMOCKA_LIBRARIES}")

set(root_url "https://raw.githubusercontent.com/RoaringBitmap/CRoaring/master/tests/")

foreach (test_src_file 
    "array_container_unit.c"
    "bitset_container_unit.c"
    "container_comparison_unit.c"
    "mixed_container_unit.c"
    "run_container_unit.c"
    "toplevel_unit.c"
    "util_unit.c"
    )
    file(DOWNLOAD
        "${root_url}${test_src_file}"
        "${CMAKE_BINARY_DIR}/${test_src_file}"
    )

    get_filename_component(test_name ${test_src_file} NAME_WE)

    add_executable(${test_name} "${CMAKE_BINARY_DIR}/${test_src_file}")

    target_include_directories(
        ${test_name}
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}
    )

    target_link_libraries(
        ${test_name}
        PRIVATE
            roaring::roaring
            cmocka::cmocka
    )

    add_test(${test_name} ${test_name})
endforeach ()
