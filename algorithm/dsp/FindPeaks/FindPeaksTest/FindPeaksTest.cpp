#include <iostream>

#include "../FindPeaks.h"


int main()
{
    double data[] = { 1, 4, 2, 2, 1, 5, 0 };
    std::deque<std::size_t> peaks;

    FindPeaks(data, sizeof(data) / sizeof(data[0]), peaks);

    for (auto pos : peaks)
        std::cout << pos << ": " << data[pos] << std::endl;

    return 0;
}
