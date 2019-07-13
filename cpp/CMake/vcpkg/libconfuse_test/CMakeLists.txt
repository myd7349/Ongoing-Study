cmake_minimum_required(VERSION 3.8)

project(libconfuse-test C)

find_package(unofficial-libconfuse CONFIG REQUIRED)

foreach (source
    annotate.c
    annotate.conf
)
    file(DOWNLOAD
        "https://raw.githubusercontent.com/martinh/libconfuse/master/tests/${source}"
        "${CMAKE_CURRENT_BINARY_DIR}/${source}"
    )
endforeach ()

add_executable(annotate ${CMAKE_CURRENT_BINARY_DIR}/annotate.c)
target_include_directories(annotate PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(annotate PRIVATE unofficial::libconfuse::libconfuse)

add_custom_command(TARGET annotate POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_BINARY_DIR}/annotate.conf"
        $<TARGET_FILE_DIR:annotate>
)
