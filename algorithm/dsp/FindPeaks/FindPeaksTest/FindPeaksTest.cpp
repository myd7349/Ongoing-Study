#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#define WITHOUT_NUMPY
#include <matplotlibcpp.h>

#include "../FindPeaks.h"
#include "../../../../cpp/read_stream.hpp"


namespace plt = matplotlibcpp;

template <typename InputIterator>
void Plot(InputIterator first, InputIterator last)
{
    std::vector<typename std::iterator_traits<InputIterator>::value_type> data(first, last);
    plt::figure_size(1200, 780);
    plt::plot(data);
}


int main()
{
    //Py_SetPath(PYTHONPATH);

#ifdef _WIN32
    _putenv("PYTHONHOME=" PYTHONHOME);
#else
    setenv("PYTHONHOME", PYTHONHOME, 0);
#endif

    double data[] = { 1, 4, 2, 2, 1, 5, 0 };
    std::deque<std::size_t> peaks;

    FindPeaks(data, sizeof(data) / sizeof(data[0]), peaks);

    for (auto pos : peaks)
        std::cout << pos << ": " << data[pos] << std::endl;

    Plot(std::cbegin(data), std::cend(data));

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


// References:
// https://stackoverflow.com/questions/38132755/importerror-no-module-named-encodings
// https://stackoverflow.com/questions/5694706/py-initialize-fails-unable-to-load-the-file-system-codec
// https://stackoverflow.com/questions/7660001/cmake-finds-wrong-python-libs
// https://stackoverflow.com/questions/10675315/setting-pythonpath-and-pythonhome
// https://github.com/ytdl-org/youtube-dl/issues/10372
// https://stackoverflow.com/questions/17258029/c-setenv-undefined-identifier-in-visual-studio
