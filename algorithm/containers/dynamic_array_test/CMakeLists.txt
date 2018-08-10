cmake_minimum_required (VERSION 3.8)
project ("dynamic_array_test")
find_library(GTest REQUIRED)
target_link_libraries(main PRIVATE GTest::GTest GTest::Main)

#add_executable (dynamic_array_test
#    "dynamic_array_test.c"
#	"../dynamic_array.c"
#	"../../algutils.c"
#	)
add_test(AllTestsInMain main)


# References:
# https://github.com/Microsoft/vcpkg/issues/1094
# https://github.com/Microsoft/vcpkg/blob/8379a80abe5288c7c06d5b9ab16efe355d1c6f62/docs/EXAMPLES.md#example-1-2-b