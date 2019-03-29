#include <algorithm>
#include <ctime>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

#include "../../../common.h"


int main()
{
    std::default_random_engine engine(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    std::vector<double> nums;
    nums.reserve(10);

    for (int i = 0; i < 10; ++i)
        nums.push_back(dist(engine));

    std::copy(nums.cbegin(), nums.cend(), std::ostream_iterator<double>(std::cout, "\n"));

    PAUSE();

    return 0;
}


// References:
// C++ Primer, 5th Edition, 17.4.2 Other Kinds of Distributions
