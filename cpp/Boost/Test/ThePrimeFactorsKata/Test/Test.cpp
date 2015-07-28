// 2015-07-28T15:21+08:00
// This example comes from a series of tutorials on doing unit test with Boost.Test.
// Please follow the first link in the `References` section to study these tutorials.
// You will have a good knowledge of test-driven development with Boost.Test after 
// you reading these posts.

#include <initializer_list>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include "../PrimeFactors/PrimeFactors.h"

static void AssertValueHasPrimeFactors(int value, const std::initializer_list<int> &expected)
{
    std::list<int> result = PrimeFactors::Generate(value);
    BOOST_REQUIRE_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
        result.cbegin(), result.cend());
}

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

// References:
// [C++ Unit Tests With Boost.Test, Part 2](https://legalizeadulthood.wordpress.com/2009/07/05/c-unit-tests-with-boost-test-part-2/)
// [Kata](https://en.wikipedia.org/wiki/Kata_%28programming%29)
// http://stackoverflow.com/questions/3795567/visual-studio-2010-not-autolinking-static-libraries-from-projects-that-are-depen
