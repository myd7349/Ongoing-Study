#include <algorithm>
#include <cstring>
#include <numeric>
#include <vector>

#include "mini_benchmark.hpp"


void BM_ShiftDownOneElement_naive(int turns)
{
    std::vector<double> data(1000);
    std::iota(data.begin(), data.end(), 0);

    for (int c = 0; c < turns; ++c)
    {
        for (std::vector<double>::size_type i = 0; i < data.size() - 1; ++i)
        {
            data[i] = data[i + 1];
        }
    }
}
BENCHMARK(BM_ShiftDownOneElement_naive)


void BM_ShiftDownOneElement_memmove(int turns)
{
    std::vector<double> data(1000);
    std::iota(data.begin(), data.end(), 0);

    for (int c = 0; c < turns; ++c)
        std::memmove(data.data(), data.data() + 1, (data.size() - 1) * sizeof(data[0]));
}
BENCHMARK(BM_ShiftDownOneElement_memmove)


void BM_ShiftDownOneElement_rotate(int turns)
{
    std::vector<double> data(1000);
    std::iota(data.begin(), data.end(), 0);

    for (int c = 0; c < turns; ++c)
    {
        std::rotate(data.begin(), data.begin() + 1, data.end());
    }
}
BENCHMARK(BM_ShiftDownOneElement_rotate)


int main()
{
    RunSpecifiedBenchmarks();

    return 0;
}
