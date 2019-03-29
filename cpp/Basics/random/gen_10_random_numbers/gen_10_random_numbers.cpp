#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>
#include <iterator>
#include <random>
#include <thread>
#include <vector>

#include "../../../common.h"
#include "../../../dividing_lines.h"


std::vector<unsigned> gen_10_random_numbers_v1(unsigned min, unsigned max)
{
    std::default_random_engine engine;
    std::uniform_int_distribution<unsigned int> dist(0, 9); // inclusive

    std::vector<unsigned> nums;
    nums.reserve(10);

    for (int i = 0; i < 10; ++i)
         nums.push_back(dist(engine));

    return nums;
}


std::vector<unsigned> gen_10_random_numbers_v2(unsigned min, unsigned max)
{
    static std::default_random_engine engine;

    std::uniform_int_distribution<unsigned int> dist(0, 9); // inclusive

    std::vector<unsigned> nums;
    nums.reserve(10);

    for (int i = 0; i < 10; ++i)
        nums.push_back(dist(engine));

    return nums;
}


std::vector<unsigned> gen_10_random_numbers_v3(unsigned min, unsigned max)
{
    std::default_random_engine engine(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<unsigned int> dist(0, 9); // inclusive

    std::vector<unsigned> nums;
    nums.reserve(10);

    for (int i = 0; i < 10; ++i)
        nums.push_back(dist(engine));

    return nums;
}


std::vector<unsigned> gen_10_random_numbers_v4(unsigned min, unsigned max)
{
    std::random_device rd;
    std::uniform_int_distribution<unsigned int> dist(0, 9); // inclusive

    std::vector<unsigned> nums;
    nums.reserve(10);

    for (int i = 0; i < 10; ++i)
        nums.push_back(dist(rd));

    return nums;
}


std::ostream &operator<<(std::ostream &os, const std::vector<unsigned> &nums)
{
    std::copy(nums.cbegin(), nums.cend(), std::ostream_iterator<unsigned>(os, " "));
    return os;
}


int main()
{
    {
        DIVIDING_LINE_1('-');

        auto nums1 = gen_10_random_numbers_v1(0, 9);
        auto nums2 = gen_10_random_numbers_v1(0, 9);

        std::cout << nums1 << std::endl;
        std::cout << nums2 << std::endl;
    }

    {
        DIVIDING_LINE_1('-');

        auto nums1 = gen_10_random_numbers_v2(0, 9);
        auto nums2 = gen_10_random_numbers_v2(0, 9);

        std::cout << nums1 << std::endl;
        std::cout << nums2 << std::endl;
    }

    {
        DIVIDING_LINE_1('-');

        auto nums = gen_10_random_numbers_v3(0, 9);

        std::cout << nums << std::endl;

        std::this_thread::sleep_for(std::chrono::microseconds(100));

        nums = gen_10_random_numbers_v3(0, 9);

        std::cout << nums << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(2));

        nums = gen_10_random_numbers_v3(0, 9);

        std::cout << nums << std::endl;
    }

    {
        DIVIDING_LINE_1('-');

        auto nums = gen_10_random_numbers_v4(0, 9);

        std::cout << nums << std::endl;

        std::this_thread::sleep_for(std::chrono::microseconds(100));

        nums = gen_10_random_numbers_v4(0, 9);

        std::cout << nums << std::endl;
    }

    PAUSE();

    return 0;
}


// References:
// C++ Primer, 5th Edition, 17.4.1 Random-Number Engines and Distribution
