// 2018-07-04T14:25+08:00

#include <algorithm>
#include <functional>

#include <benchmark/benchmark.h> // vcpkg install benchmark

#include <sigc++/sigc++.h> // For VS2017:
                           // vcpkg install libsigcpp
                           // For VS2010:
                           // https://download.gnome.org/sources/libsigc++/2.4/libsigc++-2.4.1.tar.xz


#ifdef _MSC_VER
# pragma comment(lib, "shlwapi.lib")
#endif


constexpr int DataChunkSize = 100;

using DataChunk = double[DataChunkSize];
using DataFilter = std::function<void(DataChunk &)>;


void Process(DataChunk &data)
{
    std::transform(std::begin(data), std::end(data), std::begin(data),
        [](double value) { return value /= 2.0; });
}


void Reverse(DataChunk &data)
{
    std::sort(std::begin(data), std::end(data), std::greater<double>());
}


static void BM_NormalYoungMan(benchmark::State& state)
{
    for (auto _ : state)
    {
        DataChunk data{ 1, 1, 2, 3, 5, 8, 13, 21, 34, 55 };
        Process(data);
        Reverse(data);
    }
}


BENCHMARK(BM_NormalYoungMan);


static void BM_2BYoungMan(benchmark::State& state)
{
    sigc::signal<void, DataChunk &> dataFilters;
    dataFilters.connect(&Process);
    dataFilters.connect(&Reverse);

    for (auto _ : state)
    {
        DataChunk data { 1, 1, 2, 3, 5, 8, 13, 21, 34, 55 };
        dataFilters.emit(data);
    }
}


BENCHMARK(BM_2BYoungMan);


int main(int argc, char **argv)
{
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();

    return 0;
}

