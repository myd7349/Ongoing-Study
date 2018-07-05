// 2018-07-05T14:47+08:00
#include <algorithm>
#include <cmath>
#include <cstdlib>

#include <benchmark/benchmark.h>

#ifdef _MSC_VER
# pragma comment(lib, "shlwapi.lib")
#endif


constexpr int DataChunkSize = 200;
constexpr int Dimension = 80;

using DataChunk = double[DataChunkSize];
using MultiDimensionalDataChunks = DataChunk[Dimension];


static MultiDimensionalDataChunks data;


#define PROCESS_DATA_CHUNK(chunk, op) \
    do \
    { \
        for (int pos = 0; pos < DataChunkSize; ++pos) \
            chunk[pos] = op(chunk[pos]); \
    } while (0)



inline double Zero(double v)
{
    return v = 0.0;;
}


inline double Random(double v)
{
    return v = rand();
}


inline double Double(double v)
{
    return v * 2;
}


inline double Plus42(double v)
{
    return v + 42.0;
}


inline double Sqrt(double v)
{
    return std::sqrt(v);
}


double HardWork(double v)
{
    v *= 3.141592653;

    double coff[]
    {
        0.4, 1.2, 7.7, 2.3, -800.0,
        12, 23, 45, 0, -24, 166,
        212, 456, 3.141592653,
        2.71828,
        3.141592653 / 2.0,  2.71828 * 2.71828 * v,
        3.141592653 / 4.0,  2.71828 * 2.71828 * v,
        3.141592653 / 6.0,  2.71828 * 2.71828 * v,
        3.141592653 / 8.0,  2.71828 * 2.71828 * v,
        3.141592653 / 10.0, 2.71828 * 2.71828 * v,
        3.141592653 * 2.0,  2.71828 * 2.71828 * v,
        3.141592653 * 4.0,  2.71828 * 2.71828 * v,
        3.141592653 * 6.0,  2.71828 * 2.71828 * v,
        3.141592653 * 8.0,  2.71828 * 2.71828 * v,
        3.141592653 * 10.0, 2.71828 * 2.71828 * v,
    };

    std::sort(std::begin(coff), std::end(coff));
    std::reverse(std::begin(coff), std::end(coff));

    return v += coff[sizeof(coff) / sizeof(coff[0]) / 2];
}


static void BM_OnePass(benchmark::State& state)
{
    for (auto _ : state)
    {
        for (int d = 0; d < Dimension; ++d)
        {
            for (int pos = 0; pos < DataChunkSize; ++pos)
            {
                data[d][pos] = Zero(data[d][pos]);
                data[d][pos] = Random(data[d][pos]);
                data[d][pos] = Double(data[d][pos]);
                data[d][pos] = Plus42(data[d][pos]);
                data[d][pos] = Sqrt(data[d][pos]);
                data[d][pos] = HardWork(data[d][pos]);
            }
        }
    }
}

BENCHMARK(BM_OnePass);


static void BM_MultiplePassNonFuncCall(benchmark::State& state)
{
    for (auto _ : state)
    {
        for (int d = 0; d < Dimension; ++d)
        {
            PROCESS_DATA_CHUNK(data[d], Zero);
            PROCESS_DATA_CHUNK(data[d], Random);
            PROCESS_DATA_CHUNK(data[d], Double);
            PROCESS_DATA_CHUNK(data[d], Plus42);
            PROCESS_DATA_CHUNK(data[d], Sqrt);
            PROCESS_DATA_CHUNK(data[d], HardWork);
        }
    }
}

BENCHMARK(BM_MultiplePassNonFuncCall);


#define DEFINE_DATACHUNK_PROCESSING_FUNC(fn) \
static BENCHMARK_ALWAYS_INLINE void DataChunk_##fn##_Inline(DataChunk &chunk) \
{ \
    PROCESS_DATA_CHUNK(chunk, fn); \
} \
\
static void DataChunk_##fn(DataChunk &chunk) \
{ \
    PROCESS_DATA_CHUNK(chunk, fn); \
}


DEFINE_DATACHUNK_PROCESSING_FUNC(Zero)
DEFINE_DATACHUNK_PROCESSING_FUNC(Random)
DEFINE_DATACHUNK_PROCESSING_FUNC(Double)
DEFINE_DATACHUNK_PROCESSING_FUNC(Plus42)
DEFINE_DATACHUNK_PROCESSING_FUNC(Sqrt)
DEFINE_DATACHUNK_PROCESSING_FUNC(HardWork)


static void BM_MultiplePassWithFuncCall(benchmark::State& state)
{
    for (auto _ : state)
    {
        for (int d = 0; d < Dimension; ++d)
        {
            DataChunk_Zero(data[d]);
            DataChunk_Random(data[d]);
            DataChunk_Double(data[d]);
            DataChunk_Plus42(data[d]);
            DataChunk_Sqrt(data[d]);
            DataChunk_HardWork(data[d]);
        }
    }
}

BENCHMARK(BM_MultiplePassWithFuncCall);


static void BM_MultiplePassWithInlineFuncCall(benchmark::State& state)
{
    for (auto _ : state)
    {
        for (int d = 0; d < Dimension; ++d)
        {
            DataChunk_Zero_Inline(data[d]);
            DataChunk_Random_Inline(data[d]);
            DataChunk_Double_Inline(data[d]);
            DataChunk_Plus42_Inline(data[d]);
            DataChunk_Sqrt_Inline(data[d]);
            DataChunk_HardWork_Inline(data[d]);
        }
    }
}

BENCHMARK(BM_MultiplePassWithInlineFuncCall);


BENCHMARK_MAIN()
