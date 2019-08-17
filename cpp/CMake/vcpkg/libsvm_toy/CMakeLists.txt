cmake_minimum_required(VERSION 3.9)

project(svm-toy C CXX)

find_package(unofficial-libsvm CONFIG REQUIRED)

file(DOWNLOAD
    "https://raw.githubusercontent.com/cjlin1/libsvm/master/svm-toy/windows/svm-toy.cpp"
    "${CMAKE_CURRENT_BINARY_DIR}/svm-toy.cpp"
)

function (vcpkg_replace_string filename match_string replace_string)
    file(READ ${filename} _contents)
    string(REPLACE "${match_string}" "${replace_string}" _contents "${_contents}")
    file(WRITE ${filename} "${_contents}")
endfunction ()

vcpkg_replace_string(
    "${CMAKE_CURRENT_BINARY_DIR}/svm-toy.cpp"
    "#include \"../../svm.h\""
    "#include <svm.h>"
)

add_executable(svm-toy "${CMAKE_CURRENT_BINARY_DIR}/svm-toy.cpp")
set_target_properties(svm-toy PROPERTIES WIN32_EXECUTABLE ON)
target_link_libraries(svm-toy PRIVATE unofficial::libsvm::libsvm)
