cmake_minimum_required(VERSION 3.8)

project(sx_tests C)

find_package(sx CONFIG REQUIRED)

set(test_sources
    test-bheap.c
    test-cmdline.c
    test-fiber.c
    test-hash.c
    test-ini.c
    test-jobs.c
    test-threads.c
    test-timer.c
    test-tlsf.c
    test-virtualmem.c
)

foreach (test_src ${test_sources})
    file(DOWNLOAD
        https://raw.githubusercontent.com/septag/sx/master/tests/${test_src}
        ${CMAKE_CURRENT_BINARY_DIR}/${test_src}
    )

    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${CMAKE_CURRENT_BINARY_DIR}/${test_src})
    target_link_libraries(${test_name} PRIVATE sx::sx)
endforeach ()
