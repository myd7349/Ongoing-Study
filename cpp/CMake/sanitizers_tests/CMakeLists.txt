cmake_minimum_required(VERSION 3.8)

project(asan_tests CXX)

file(DOWNLOAD
    "https://raw.githubusercontent.com/googleapis/google-cloud-cpp/v0.9.x/cmake/EnableSanitizers.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/EnableSanitizers.cmake"
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR}/cmake)

include(EnableSanitizers)

set(test_sources
    global_out_of_bounds.cpp
    heap_out_of_bounds.cpp
    stack_out_of-bounds.cpp
    use_after_free.cpp
)

foreach (test_src ${test_sources})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})
endforeach ()


# References:
# cJson/CMakeLists.txt
# https://github.com/google/sanitizers/wiki/AddressSanitizer
# https://stackoverflow.com/questions/44320465/whats-the-proper-way-to-enable-addresssanitizer-in-cmake-that-works-in-xcode
# https://github.com/googleapis/google-cloud-cpp/blob/v0.9.x/cmake/EnableSanitizers.cmake
# https://github.com/google/sanitizers
# https://github.com/kkos/oniguruma/issues/61
# http://www.cnblogs.com/hugetong/p/8260076.html
# https://wizardforcel.gitbooks.io/100-gcc-tips/content/address-sanitizer.html
# https://www.ibm.com/developerworks/cn/linux/1608_tengr_kasan/index.html
# https://github.com/kkos/oniguruma/issues/61
# https://github.com/fffaraz/awesome-cpp/issues/683
# https://github.com/google/sanitizers/wiki/AddressSanitizerOneDefinitionRuleViolation
# raylib
# zeromq
# simdjson
# https://github.com/martinus/robin-hood-hashing/blob/master/CMakeLists.txt
