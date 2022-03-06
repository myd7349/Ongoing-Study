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
# https://github.com/googleapis/google-cloud-cpp/pull/2737
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
# https://github.com/arximboldi/immer/blob/2e421eee7d1298688a2b9cfa73bd24620cc2af26/CMakeLists.txt#L23
# https://github.com/nanomsg/nng/blob/master/cmake/CheckSanitizer.cmake
# https://github.com/CaseyCarter/cmcstl2/blob/master/config/cmake/FindSanitizer.cmake
# https://github.com/lighttransport/nnview/tree/master/cmake/sanitizers
# https://github.com/lighttransport/nanort/tree/master/cmake
# https://github.com/simdjson/simdjson/blob/76b0bfa7f5f0cc74b5fec8244d6f9cda96e67872/simdjson-flags.cmake#L80-L89
# target_compile_options(simdjson-flags INTERFACE -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined -fno-sanitize-recover=all)
# target_link_libraries(simdjson-flags INTERFACE -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined -fno-sanitize-recover=all)
# 
# [undefined reference to '_asan_init_v4' when compiling](https://stackoverflow.com/questions/42482494/undefined-reference-to-asan-init-v4-when-compiling)
# [How to use AddressSanitizer with GCC?](https://stackoverflow.com/questions/37970758/how-to-use-addresssanitizer-with-gcc)
# https://clang.llvm.org/docs/AddressSanitizer.html
# [How I'm supposed to use the sanitizer in clang?](https://stackoverflow.com/questions/22699881/how-im-supposed-to-use-the-sanitizer-in-clang)
# https://lemire.me/blog/2016/04/20/no-more-leaks-with-sanitize-flags-in-gcc-and-clang/
# https://github.com/pingcap/tiflash/blob/v6.0.0/cmake/sanitize.cmake
# https://github.com/StableCoder/cmake-scripts/blob/main/sanitizers.cmake
# https://github.com/p-ranav/glob/blob/master/cmake/tools.cmake
