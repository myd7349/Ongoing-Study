// 2015-06-04T14:14+08:00
#include <algorithm>
#include <cassert>
#include <cstring>
#include <numeric>
#include <vector>

#include "benchmark/benchmark.h"

#ifdef _MSC_VER
# pragma comment(lib, "shlwapi.lib")
#endif

namespace {
void BM_ShiftDownOneElement_naive(benchmark::State &state)
{
    assert(state.range_x() > 1);

    std::vector<double> data(state.range_x());
    std::iota(data.begin(), data.end(), 0);

    while (state.KeepRunning()) {
        for (auto i = 0; i < data.size() - 1; ++i) {
            data[i] = data[i + 1];
        }
    }
}

void BM_ShiftDownOneElement_memmove(benchmark::State &state)
{
    assert(state.range_x() > 1);

    std::vector<double> data(state.range_x());
    std::iota(data.begin(), data.end(), 0);

    while (state.KeepRunning()) {
        std::memmove(data.data(), data.data() + 1, (data.size() - 1) * sizeof(data[0]));
    }
}

void BM_ShiftDownOneElement_rotate(benchmark::State &state)
{
    assert(state.range_x() > 1);

    std::vector<double> data(state.range_x());
    std::iota(data.begin(), data.end(), 0);

    while (state.KeepRunning()) {
        std::rotate(data.begin(), data.begin() + 1, data.end());
    }
}
}

BENCHMARK(BM_ShiftDownOneElement_naive)->Arg(1000)->Arg(10000)->Arg(100000);
BENCHMARK(BM_ShiftDownOneElement_memmove)->Arg(1000)->Arg(10000)->Arg(100000);
BENCHMARK(BM_ShiftDownOneElement_rotate)->Arg(1000)->Arg(10000)->Arg(100000);

BENCHMARK_MAIN();

// Dependencies:
// [benchmark 0.1.0](https://github.com/google/benchmark)

// References:
// [Shifting elements of an array?](http://www.cplusplus.com/forum/beginner/1936/)
// [How to use and when is good use memmove in C?](http://stackoverflow.com/questions/9041787/how-to-use-and-when-is-good-use-memmove-in-c)
// [Optimal way to perform a shift operation on an array](http://stackoverflow.com/questions/1903190/optimal-way-to-perform-a-shift-operation-on-an-array)
