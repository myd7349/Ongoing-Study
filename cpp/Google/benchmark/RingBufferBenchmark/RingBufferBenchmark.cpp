#include <benchmark/benchmark.h>

#include <boost/circular_buffer.hpp>

#include "../../../C++11/ring_buffer.hpp"


static void BM_NonThreadSafeRingBuffer(benchmark::State &state)
{
    double value;
    NonThreadSafeRingBuffer<double, 1000> buffer;

    for (auto _ : state)
    {
        buffer.Push(3.1415926);
        buffer.Push(2.71828);

        buffer.Pop(value);

        buffer.Push(3.1415926);

        buffer.Pop(value);
        buffer.Pop(value);
        buffer.Pop(value);

        buffer.Push(42);

        buffer.Pop(value);

        buffer.Push(0);

        buffer.Pop(value);
    }
}


static void BM_Boost_circular_buffer(benchmark::State &state)
{
    boost::circular_buffer<double> buffer(1000);
    
    for (auto _ : state)
    {
        buffer.push_back(3.1415926);
        buffer.push_back(2.71828);

        buffer.pop_back();

        buffer.push_back(3.1415926);

        buffer.pop_back();
        buffer.pop_back();

        buffer.push_back(42);

        buffer.pop_back();

        buffer.push_back(0);

        buffer.pop_back();
    }
}


static void BM_WaitFreeRingBuffer(benchmark::State &state)
{
    double value;
    WaitFreeRingBuffer<double, 1000> buffer;

    for (auto _ : state)
    {
        buffer.Push(3.1415926);
        buffer.Push(2.71828);

        buffer.Pop(value);

        buffer.Push(3.1415926);

        buffer.Pop(value);
        buffer.Pop(value);
        buffer.Pop(value);

        buffer.Push(42);

        buffer.Pop(value);

        buffer.Push(0);

        buffer.Pop(value);
    }
}


BENCHMARK(BM_Boost_circular_buffer);
BENCHMARK(BM_NonThreadSafeRingBuffer);
BENCHMARK(BM_WaitFreeRingBuffer);
