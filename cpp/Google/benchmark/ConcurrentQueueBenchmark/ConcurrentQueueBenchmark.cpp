#include <queue>

#include <benchmark/benchmark.h>

#include <concurrent_queue.h>

#include <blockingconcurrentqueue.h>
#include <concurrentqueue.h>
#include <readerwriterqueue.h>


static void BM_STL_queue(benchmark::State &state)
{
    std::queue<double> queue;

    for (auto _ : state)
    {
        queue.push(3.1415926);
        queue.push(2.71828);

        queue.pop();

        queue.push(3.1415926);

        queue.pop();
        queue.pop();

        queue.push(42);

        queue.pop();

        queue.push(0);

        queue.pop();
    }
}


static void BM_MSVC_concurrent_queue(benchmark::State &state)
{
    double value;
    Concurrency::concurrent_queue<double> queue;

    for (auto _ : state)
    {
        queue.push(3.1415926);
        queue.push(2.71828);

        queue.try_pop(value);

        queue.push(3.1415926);

        queue.try_pop(value);
        queue.try_pop(value);
        queue.try_pop(value);

        queue.push(42);

        queue.try_pop(value);

        queue.push(0);

        queue.try_pop(value);
    }
}


static void BM_moodycamel_BlockingConcurrentQueue(benchmark::State &state)
{
    double value;
    moodycamel::BlockingConcurrentQueue<double> queue;

    for (auto _ : state)
    {
        queue.enqueue(3.1415926);
        queue.enqueue(2.71828);

        queue.try_dequeue(value);

        queue.enqueue(3.1415926);

        queue.try_dequeue(value);
        queue.try_dequeue(value);
        queue.try_dequeue(value);

        queue.enqueue(42);

        queue.try_dequeue(value);

        queue.enqueue(0);

        queue.try_dequeue(value);
    }
}


static void BM_moodycamel_ConcurrentQueue(benchmark::State &state)
{
    double value;
    moodycamel::ConcurrentQueue<double> queue;

    for (auto _ : state)
    {
        queue.enqueue(3.1415926);
        queue.enqueue(2.71828);

        queue.try_dequeue(value);

        queue.enqueue(3.1415926);

        queue.try_dequeue(value);
        queue.try_dequeue(value);
        queue.try_dequeue(value);

        queue.enqueue(42);

        queue.try_dequeue(value);

        queue.enqueue(0);

        queue.try_dequeue(value);
    }
}


static void BM_moodycamel_ReaderWriterQueue(benchmark::State &state)
{
    double value;
    moodycamel::ReaderWriterQueue<double> queue;

    for (auto _ : state)
    {
        queue.enqueue(3.1415926);
        queue.enqueue(2.71828);

        queue.try_dequeue(value);

        queue.enqueue(3.1415926);

        queue.try_dequeue(value);
        queue.try_dequeue(value);
        queue.try_dequeue(value);

        queue.enqueue(42);

        queue.try_dequeue(value);

        queue.enqueue(0);

        queue.try_dequeue(value);
    }
}


BENCHMARK(BM_STL_queue);
BENCHMARK(BM_MSVC_concurrent_queue);
BENCHMARK(BM_moodycamel_BlockingConcurrentQueue);
BENCHMARK(BM_moodycamel_ConcurrentQueue);
BENCHMARK(BM_moodycamel_ReaderWriterQueue);


// References:
// https://stackoverflow.com/questions/7817364/are-there-any-concurrent-containers-in-c11
// https://msdn.microsoft.com/en-us/library/ee355358.aspx
// https://github.com/kingsamchen/Eureka/blob/master/BlockingQueue/src/blocking_queue.h
// https://github.com/cameron314/concurrentqueue
// https://github.com/cameron314/readerwriterqueue
