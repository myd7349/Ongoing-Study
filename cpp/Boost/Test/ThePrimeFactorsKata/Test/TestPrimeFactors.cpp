// 2015-07-29T11:44+08:00

#include <initializer_list>

#include <boost/test/unit_test.hpp>

#include "PrimeFactors.h"

static void AssertValueHasPrimeFactors(int value, const std::initializer_list<int> &expected)
{
    std::list<int> result = PrimeFactors::Generate(value);
    BOOST_REQUIRE_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
        result.cbegin(), result.cend());
}

BOOST_AUTO_TEST_SUITE(PrimeFactorsSuite)

BOOST_AUTO_TEST_CASE(OneHasNoFactors)
{
    std::list<int> result = PrimeFactors::Generate(1);
    BOOST_REQUIRE_EQUAL(0, result.size());
}

BOOST_AUTO_TEST_CASE(TwoHasOneFactor)
{
    AssertValueHasPrimeFactors(2, { 2 });
}

BOOST_AUTO_TEST_CASE(ThreeHasOneFactor)
{
    AssertValueHasPrimeFactors(3, { 3 });
}

BOOST_AUTO_TEST_CASE(FourHasTwoFactors)
{
    AssertValueHasPrimeFactors(4, { 2, 2 });
}

BOOST_AUTO_TEST_CASE(SixHasTwoFactors)
{
    AssertValueHasPrimeFactors(6, { 2, 3 });
}

BOOST_AUTO_TEST_CASE(EightHasThreeFactors)
{
    AssertValueHasPrimeFactors(8, { 2, 2, 2 });
}

BOOST_AUTO_TEST_CASE(NineHasTwoFactors)
{
    AssertValueHasPrimeFactors(9, { 3, 3 });
}

BOOST_AUTO_TEST_SUITE_END()

// References:
// [C++ Unit Tests With Boost.Test, Part 2](https://legalizeadulthood.wordpress.com/2009/07/05/c-unit-tests-with-boost-test-part-2/)
// [Kata](https://en.wikipedia.org/wiki/Kata_%28programming%29)
// http://stackoverflow.com/questions/3795567/visual-studio-2010-not-autolinking-static-libraries-from-projects-that-are-depen
