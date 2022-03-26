#include <iomanip>
#include <iostream>
#include <numeric>
#include <set>
#include <unordered_set>
#include <vector>

#include "../../Stopwatch.h"
#include "../../common.h"


template <typename T, typename ContainerT>
void Benchmark(typename ContainerT::size_type size, const char *typeName)
{
    std::vector<T> source(size);
    std::iota(source.begin(), source.end(), 0);

    Stopwatch sw;
    sw.Start();

    ContainerT set(source.cbegin(), source.cend());

    sw.Stop();

    LONGLONG elapsedMs = sw.GetElapsedMilliseconds();

    std::cout << std::left << std::setw(20) << typeName << std::right
        << std::setw(15) << size << std::setw(15) << elapsedMs << "ms\n";
}


template <typename T>
inline void Benchmark_set(typename std::set<T>::size_type size)
{
    Benchmark<T, std::set<T>>(size, "std::set");
}


template <typename T>
inline void Benchmark_unordered_set(typename std::set<T>::size_type size)
{
    Benchmark<T, std::unordered_set<T>>(size, "std::unordered_set");
}



int main()
{
    Benchmark<int, std::vector<int>>(100, "std::vector");
    Benchmark<int, std::vector<int>>(10000, "std::vector");
    Benchmark<int, std::vector<int>>(1000000, "std::vector");
    Benchmark<int, std::vector<int>>(10000000, "std::vector");

    Benchmark_set<int>(100);
    Benchmark_set<int>(10000);
    Benchmark_set<int>(1000000);
    Benchmark_set<int>(10000000);

    Benchmark_unordered_set<int>(100);
    Benchmark_unordered_set<int>(10000);
    Benchmark_unordered_set<int>(1000000);
    Benchmark_unordered_set<int>(10000000);

    Benchmark_unordered_set<int>(20000000);

    PAUSE();

    return 0;
}


// References:
// https://stackoverflow.com/questions/17566141/filling-unordered-set-is-too-slow
// https://stackoverflow.com/questions/24506789/set-vs-unordered-set-for-fastest-iteration
