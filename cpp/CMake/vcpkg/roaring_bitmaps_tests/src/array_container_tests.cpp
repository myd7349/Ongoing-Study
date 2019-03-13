#if 0
extern "C"
{
#include <roaring/containers/array.h>
}
#else
#include <roaring/roaring.h>
#endif

#include <gtest/gtest.h>


// https://github.com/RoaringBitmap/CRoaring/blob/master/tests/array_container_unit.c#L31
TEST(ArrayContainerTests, AddExisted)
{
    array_container_t *arr = array_container_create();
    EXPECT_TRUE(arr != nullptr);

    int expected_card = 0;

    for (auto i = 0; i < (1 << 16); i += 3)
    {
        EXPECT_TRUE(array_container_add(arr, i));
        EXPECT_TRUE(array_container_contains(arr, i));
        EXPECT_EQ(arr->cardinality, ++expected_card);
        EXPECT_FALSE(arr->cardinality > arr->cardinality);
    }

    for (auto i = 0; i < (1 << 16); ++i)
        EXPECT_EQ(array_container_contains(arr, i), (i / 3 * 3 == i));

    EXPECT_EQ(array_container_cardinality(arr), (1 << 16) / 3 + 1);

    for (auto i = 0; i < (1 << 16); i += 3)
    {
        EXPECT_TRUE(array_container_contains(arr, i));
        EXPECT_TRUE(array_container_remove(arr, i));
        EXPECT_EQ(arr->cardinality, --expected_card);
        EXPECT_FALSE(array_container_contains(arr, i));
    }

    EXPECT_EQ(array_container_cardinality(arr), 0);

    for (int i = 65535; i >= 0; i -= 3)
    {
        EXPECT_TRUE(array_container_add(arr, i));
        EXPECT_TRUE(array_container_contains(arr, i));
        EXPECT_EQ(arr->cardinality, ++expected_card);
        EXPECT_FALSE(arr->cardinality > arr->capacity);
    }

    EXPECT_EQ(array_container_cardinality(arr), expected_card);

    for (int i = 0; i < (1 << 16); ++i)
        EXPECT_EQ(array_container_contains(arr, i), (i / 3 * 3 == i));

    for (int i = 0; i < (1 << 16); i += 3)
    {
        EXPECT_TRUE(array_container_contains(arr, i));
        EXPECT_TRUE(array_container_remove(arr, i));
        EXPECT_EQ(arr->cardinality, --expected_card);
        EXPECT_FALSE(array_container_contains(arr, i));
    }

    array_container_free(arr);
}

