cmake_minimum_required (VERSION 3.8)

project (tcpclient C)

add_executable (tcpclient
    "tcpclient.c"
	"../get_in_addr.c"
	"../../ttoi.c")

# Currently, find_package does work with `getopt-win32` when using vcpkg.
if(WIN32)
    target_include_directories(tcpclient PRIVATE "$ENV{VCPKG_DIR}/installed/x86-windows/include")
    target_link_libraries(tcpclient PRIVATE "$ENV{VCPKG_DIR}/installed/x86-windows/lib/getopt.lib")
    add_custom_command(TARGET tcpclient POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$ENV{VCPKG_DIR}/installed/x86-windows/bin/getopt.dll"
            $<TARGET_FILE_DIR:tcpclient>)
endif()


# References:
# https://stackoverflow.com/questions/13703647/how-to-properly-add-include-directories-with-cmake
