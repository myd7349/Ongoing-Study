// 2015-07-28T15:21+08:00
// This example comes from a series of tutorials on doing unit test with Boost.Test.
// Please follow the first link in the `References` section to read these tutorials.

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include "../PrimeFactors/PrimeFactors.h"

BOOST_AUTO_TEST_CASE(OneHasNoFactors)
{
    std::list<int> result = PrimeFactors::Generate(1);
    BOOST_REQUIRE_EQUAL(0, result.size());
}

// References:
// [C++ Unit Tests With Boost.Test, Part 2](https://legalizeadulthood.wordpress.com/2009/07/05/c-unit-tests-with-boost-test-part-2/)
// [Kata](https://en.wikipedia.org/wiki/Kata_%28programming%29)
// http://stackoverflow.com/questions/3795567/visual-studio-2010-not-autolinking-static-libraries-from-projects-that-are-depen
