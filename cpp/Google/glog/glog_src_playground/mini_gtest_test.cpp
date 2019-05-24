#include "mini_gtest.hpp"


TEST(Math, Add)
{
    EXPECT_EQ(1 + 2, 3);
}


TEST(Math, Minus)
{
    EXPECT_EQ(1 - 2, -1);
}


int main()
{
    RUN_ALL_TESTS();
    return 0;
}