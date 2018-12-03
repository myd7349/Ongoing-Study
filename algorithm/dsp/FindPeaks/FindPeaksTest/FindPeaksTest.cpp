#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "../FindPeaks.h"
#include "../../../../cpp/read_stream.hpp"


int main()
{
    double data[] = { 1, 4, 2, 2, 1, 5, 0 };
    std::deque<std::size_t> peaks;

    FindPeaks(data, sizeof(data) / sizeof(data[0]), peaks);

    for (auto pos : peaks)
        std::cout << pos << ": " << data[pos] << std::endl;

    std::ifstream in("data2.txt");
    if (in.is_open())
    {
        auto lines = read_stream(in);

        auto stof = [](const std::string &s) { return std::stof(s); };

        std::vector<double> data(lines.size());
        std::transform(lines.cbegin(), lines.cend(), data.begin(), stof);

        FindPeaks(data.data(), data.size(), peaks, NAN, 5, 0.0, EdgeRising, false, true);

        std::copy(peaks.cbegin(), peaks.cend(),
            std::ostream_iterator<std::size_t>(std::cout, " "));
        std::cout << std::endl;
    }

    return 0;
}
