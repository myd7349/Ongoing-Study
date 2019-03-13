find_package(GTest MODULE REQUIRED)
find_package(roaring CONFIG REQUIRED)

enable_testing()

add_executable(
    roaring_bitmaps_tests
	array_container_tests.cpp
	cpp_class_test.cpp
)

target_link_libraries(
    roaring_bitmaps_tests
    PRIVATE
        GTest::GTest
        GTest::Main
        roaring::roaring
)

add_test(RoaringBitmapsTests roaring_bitmaps_tests)
