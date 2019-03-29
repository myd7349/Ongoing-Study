#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>

#include "../../../common.h"


std::string str_repeat(const char *p, unsigned count)
{
    if (count == 0)
        return "";

    std::string s;
    for (unsigned i = 0; i < count; ++i)
        s += p;

    return s;
}


int main()
{
    std::default_random_engine engine(static_cast<unsigned>(std::time(nullptr)));
    std::normal_distribution<> dist(4.0, 1.5); // mean 4, standard deviation 1.5

    std::vector<long> stats(9);

    for (int i = 0; i != 200; ++i)
    {
        std::vector<long>::size_type v = std::lround(dist(engine));
        if (v < stats.size())
            ++stats[v];
    }

    std::transform(
        stats.cbegin(), stats.cend(),
        std::ostream_iterator<std::string>(std::cout, "\n"),
        [](long v) { return str_repeat("\u2588", v); });

    std::cout << "\n\n";

    auto factor = 2;
    auto minmax = std::minmax_element(stats.cbegin(), stats.cend());
    auto min = *minmax.first / factor;
    auto max = *minmax.second / factor;

    for (auto i = max; i != min; --i)
    {
        std::transform(
            stats.cbegin(), stats.cend(),
            std::ostream_iterator<std::string>(std::cout, ""),
            [factor, i](long v) { return v / factor >= i ? "\u2588" : "\u0020\u0020"; });

        std::cout << '\n';
    }

    PAUSE();

    return 0;
}


// References:
// C++ Primer, 5th Edition, 17.4.2 Other Kinds of Distributions
// https://stackoverflow.com/questions/38551750/unicode-doesnt-output-correctly-windows-10
// https://stackoverflow.com/questions/12015571/how-to-print-unicode-character-in-c
// https://stackoverflow.com/questions/17103925/how-well-is-unicode-supported-in-c11
// https://stackoverflow.com/questions/166630/how-to-repeat-a-string-a-variable-number-of-times-in-c
// https://codereview.stackexchange.com/questions/114295/repeating-a-stdstring-n-times
