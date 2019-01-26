cmake_minimum_required(VERSION 3.9)

project(main C)

find_package(LibXml2 REQUIRED)

foreach(_f "gjobread.c" "gjobs.xml")
    file(DOWNLOAD
        "https://raw.githubusercontent.com/GNOME/libxml2/master/example/${_f}"
        "${CMAKE_SOURCE_DIR}/${_f}")
endforeach()

add_executable(gjobread "gjobread.c")

target_include_directories(gjobread PRIVATE ${LIBXML2_INCLUDE_DIR})
target_link_libraries(gjobread PRIVATE ${LIBXML2_LIBRARIES})
