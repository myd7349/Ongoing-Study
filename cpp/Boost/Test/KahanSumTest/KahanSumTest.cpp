// 2015-07-27T14:30+08:00
#include <cfloat>
#include <numeric>
#include <vector>

#define BOOST_TEST_MAIN
#include <boost/test/floating_point_comparison.hpp>
#include <boost/test/unit_test.hpp>

#include "../../Accumulators/KahanSum/kahan_sum.hpp"

struct KahanSumFixture
{
    KahanSumFixture() : nums_(10, 0.1) {}

    std::vector<double> nums_;
    double sum_;
};

BOOST_FIXTURE_TEST_CASE(KahanSum, KahanSumFixture)
{
    sum_ = kahan_sum(nums_.cbegin(), nums_.cend());

    BOOST_REQUIRE_EQUAL(sum_, 1.0);
    BOOST_REQUIRE_CLOSE(sum_, 1.0, DBL_EPSILON);
}

BOOST_FIXTURE_TEST_CASE(NormalAccumulate, KahanSumFixture)
{
    sum_ = std::accumulate(nums_.cbegin(), nums_.cend(), 0.0);

    // Use CHECK instead of REQUIRE here, then we will also see the
    // failing message of the next assertion.
    BOOST_REQUIRE_CLOSE(sum_, 1.0, 0.001);
    BOOST_CHECK_EQUAL(sum_, 1.0);
    BOOST_REQUIRE_CLOSE(sum_, 1.0, DBL_EPSILON);
}

// References:
// [C++ Unit Tests With Boost.Test](https://legalizeadulthood.wordpress.com/2009/07/04/c-unit-tests-with-boost-test-part-1/)
// http://www.alittlemadness.com/2009/03/31/c-unit-testing-with-boosttest/
// [C++ Unit Testing Framework: A Boost Test Tutorial](http://www.beroux.com/english/articles/boost_unit_testing/)
// http://www.zhihu.com/question/32304267
// www.boost.org/doc/libs/1_53_0/libs/test/doc/html/utf/testing-tools/floating_point_comparison.html
