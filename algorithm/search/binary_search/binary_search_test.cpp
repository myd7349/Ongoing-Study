#include <list>
#include <numeric>
#include <vector>

#include <gtest/gtest.h>

#include "binary_search.hpp"


TEST(BinarySearchTestCase, TestOnList)
{
    auto SIZE = 100;
    std::list<int> data(SIZE);
    std::iota(data.begin(), data.end(), 0);

    EXPECT_FALSE(::binary_search(data.cbegin(), data.cend(), -1));
    EXPECT_FALSE(::binary_search(data.cbegin(), data.cend(), 100));

    for (auto i : data)
        EXPECT_TRUE(::binary_search(data.cbegin(), data.cend(), i));
}


TEST(BinarySearchTestCase, TestOnVector)
{
    auto SIZE = 100;
    std::vector<int> data(SIZE);
    std::iota(data.begin(), data.end(), 0);

    EXPECT_FALSE(::binary_search(data.cbegin(), data.cend(), -1));
    EXPECT_FALSE(::binary_search(data.cbegin(), data.cend(), 100));

    for (auto i : data)
        EXPECT_TRUE(::binary_search(data.cbegin(), data.cend(), i));
}


TEST(BinarySearchTestCase, TestWithCustomPred)
{
    auto SIZE = 100;
    std::vector<int> data(SIZE);
    std::iota(data.begin(), data.end(), 0);
    std::reverse(data.begin(), data.end());

    EXPECT_FALSE(::binary_search(data.cbegin(), data.cend(), -1, std::greater<int>()));
    EXPECT_FALSE(::binary_search(data.cbegin(), data.cend(), 100, std::greater<int>()));

    for (auto i : data)
        EXPECT_TRUE(::binary_search(data.cbegin(), data.cend(), i, std::greater<int>()));
}

