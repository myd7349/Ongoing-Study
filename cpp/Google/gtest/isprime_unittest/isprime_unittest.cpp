#include <algorithm>
#include <cstdint>
#include <limits>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include "../../../../algorithm/math/NumberTheory/is_prime.h"


TEST(IsPrimeTest, TestOnPrimes)
{
    int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
    for (auto num : primes)
        EXPECT_TRUE(is_prime(num));
}


TEST(IsPrimeTest, TestOnNonPrimes)
{
    EXPECT_FALSE(is_prime(1));
    EXPECT_FALSE(is_prime(4));
    EXPECT_FALSE(is_prime(6));
    EXPECT_FALSE(is_prime(8));
    EXPECT_FALSE(is_prime(9));
}


class PrimeTestOnRandomNumbers : public testing::Test
{
protected:
    virtual void SetUp()
    {
        std::random_device rd;
        std::mt19937 engine(rd());
        std::uniform_int_distribution<std::int16_t> dist(3);

        const int Count = 10000;

        std::vector<int> xs(Count);
        std::generate(xs.begin(), xs.end(), [&dist, &engine]() { return dist(engine); });

        std::vector<int> ys(Count);
        std::generate(ys.begin(), ys.end(), [&dist, &engine]() { return dist(engine); });

        non_primes_.resize(Count);
        std::transform(xs.cbegin(), xs.cend(), ys.cbegin(), non_primes_.begin(),
            [](std::int16_t x, std::int16_t y) -> std::int32_t
            {
                return static_cast<std::int32_t>(x) * y;
            });
    }

    std::vector<int> xs_;
    std::vector<int> ys_;
    std::vector<int> non_primes_;
};

TEST_F(PrimeTestOnRandomNumbers, TestOnRandomNumbers)
{
    for (auto num : non_primes_)
        EXPECT_FALSE(is_prime(num));
}
