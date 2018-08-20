#include <vector>

#include <benchmark/benchmark.h>

#include <concurrent_vector.h>


static void BM_STL_vector(benchmark::State &state)
{
    std::vector<double> vec;

    for (auto _ : state)
    {
        vec.push_back(3.1415926);
        vec.push_back(2.71828);
        vec.push_back(3.1415926);
        vec.push_back(42);
        vec.push_back(0);
    }
}


static void BM_MSVC_concurrent_vector(benchmark::State &state)
{
    Concurrency::concurrent_vector<double> vec;

    for (auto _ : state)
    {
        vec.push_back(3.1415926);
        vec.push_back(2.71828);
        vec.push_back(3.1415926);
        vec.push_back(42);
        vec.push_back(0);
    }
}


BENCHMARK(BM_STL_vector);
BENCHMARK(BM_MSVC_concurrent_vector);


// References:
// https://stackoverflow.com/questions/7817364/are-there-any-concurrent-containers-in-c11
// https://msdn.microsoft.com/en-us/library/ee355358.aspx
