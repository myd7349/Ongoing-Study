#include <cstdint>

#include <roaring/roaring.hh>

#include <gtest/gtest.h>


// https://github.com/RoaringBitmap/CRoaring/blob/master/tests/cpp_unit.cpp#L452
TEST(CPPClassTest, AddRemoveTest)
{
    Roaring roaring;

    std::uint32_t values[4] = { 123, 9999, 0xFFFFFFF7, 0xFFFFFFFF };

    for (int i = 0; i < 4; ++i)
    {
        EXPECT_TRUE(roaring.addChecked(values[i]));
        EXPECT_FALSE(roaring.addChecked(values[i]));
    }

    for (int i = 0; i < 4; ++i)
    {
        EXPECT_TRUE(roaring.removeChecked(values[i]));
        EXPECT_FALSE(roaring.removeChecked(values[i]));
    }

    EXPECT_TRUE(roaring.isEmpty());
}
