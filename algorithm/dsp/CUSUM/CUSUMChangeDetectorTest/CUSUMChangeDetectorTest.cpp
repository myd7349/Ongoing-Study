#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

#include "../CUSUMChangeDetector.h"


int main()
{
    std::random_device rd;

    std::vector<double> data;
    
    {
        std::uniform_real_distribution<double> dist(0.0, 10.0);
        std::generate_n(std::back_inserter(data), 1000, [&]() { return dist(rd); });
    }

    {
        std::uniform_real_distribution<double> dist(100.0, 200.0);
        std::generate_n(std::back_inserter(data), 100, [&]() { return dist(rd); });
    }

    {
        std::uniform_real_distribution<double> dist(0.0, 10.0);
        std::generate_n(std::back_inserter(data), 200, [&]() { return dist(rd); });
    }

    {
        std::uniform_real_distribution<double> dist(100.0, 1000.0);
        std::generate_n(std::back_inserter(data), 200, [&]() { return dist(rd); });
    }

    CUSUMChangeDetector cd(0.05, 3.0, 50);

    int index = 0;

    for (auto xi : data)
    {
        cd.Update(xi);

        if (cd.IsChange())
        {
            std::cout << index << std::endl;
            cd.Reset();
        }

        index += 1;
    }

    std::cout << "Press any key to quit!\n";
    std::cin.get();

    return 0;
}
