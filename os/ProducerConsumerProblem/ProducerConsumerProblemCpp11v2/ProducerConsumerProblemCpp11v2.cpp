#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <thread>
#include <unordered_set>
#include <vector>

#undef HAS_BOOST
#define HAS_BOOST 0

#if HAS_BOOST
# include <boost/thread/externally_locked_stream.hpp>
using ostream_t = boost::externally_locked_stream<std::ostream>;
#else
using ostream_t = std::ostream;
#endif

#include "../../../cpp/C++11/circular_buffer.hpp"
#include "../../../cpp/C++11/semaphore.hpp"
#include "../../../cpp/common.h"
#include "../../../cpp/dividing_lines.h"
#undef ARRAYSIZE
#include "../../../cpp/Stopwatch.h"


#define PRODUCER_DO_MY_BEST (1)
#define CONSUMER_DO_MY_BEST (1)

#define ENABLE_LOGGING (1)


class ProducerConsumerContext
{
public:
    ProducerConsumerContext(ostream_t &os, std::size_t totalSize, size_t bufferSize,
        bool enableLogging = true)
        : os_(os), totalSize_(totalSize), buffer_(bufferSize),
        fullCount_(0), emptyCount_(static_cast<int>(bufferSize)),
        enableLogging_(enableLogging)
    {
    }

    void Produce(const int *items, std::size_t &count)
    {
        assert(count <= buffer_.Capacity());

        Log("Producer is trying to get the lock...\n");

#if PRODUCER_DO_MY_BEST
        int slots = static_cast<int>(count);
        int timeout = 0;

#if 0
        while (!emptyCount_.TryAcquire(slots, timeout))
        {
            slots = std::min<int>(count, emptyCount_.Available());
            if (slots == 0)
                slots = count;

            if (slots == 1)
                timeout = -1;
        }
#else
        while (!emptyCount_.TryAcquire(slots, timeout))
        {
            if (slots > 1)
                slots -= 1;
            else
                timeout = -1;
        }
#endif

        count = static_cast<std::size_t>(slots);
#else
        emptyCount_.Acquire(count);
#endif

        {
            Log("Producer gets the lock...\n");

            std::unique_lock<std::mutex> lock(bufferMutex_);
            buffer_.PushBackMany(items, count);

            Log("Produce ", count, " items.\n");
        }

        fullCount_.Release(count);
    }

    void Consume(int *items, std::size_t &count)
    {
        assert(count <= buffer_.Capacity());

        Log("\tConsumer is trying to get the lock...\n");

#if CONSUMER_DO_MY_BEST
        int slots = static_cast<int>(count);
        int timeout = 0;

#if 0
        while (!fullCount_.TryAcquire(slots, timeout))
        {
            slots = std::min<int>(count, fullCount_.Available());
            if (slots == 0)
                slots = count;

            if (slots == 1)
                timeout = -1;
        }
#else
        while (!fullCount_.TryAcquire(slots, timeout))
        {
            if (slots > 1)
                slots -= 1;
            else
                timeout = -1;
        }
#endif

        count = static_cast<std::size_t>(slots);
#else
        fullCount_.Acquire(count);
#endif

        {
            Log("\tConsumer gets the lock...\n");

            std::unique_lock<std::mutex> lock(bufferMutex_);
            buffer_.PopFrontMany(items, count);

            Log("\tConsume ", count, " items.\n");
        }

        emptyCount_.Release(count);
    }

    void SaveData(int *items, std::size_t count)
    {
        std::unique_lock<std::mutex> lock(sinkMutex_);
        sink_.reserve(sink_.size() + count);
        std::copy(items, items + count, std::back_inserter(sink_));
    }

    template <typename ...TParams>
    void Log(TParams &&...params)
    {
        if (!enableLogging_)
            return;

        std::unique_lock<std::mutex> lock(osMutex_);

        std::ostringstream oss;
        oss << "[" << std::this_thread::get_id() << "]\t[" << buffer_.Size() << "]\t";
        LogImpl(oss, std::forward<TParams>(params)...);
        os_ << oss.str();
    }

    bool IsTestPassed()
    {
        if (sink_.size() != totalSize_)
            return false;

        std::unordered_set<int> set(sink_.cbegin(), sink_.cend());
        if (set.size() != sink_.size())
            return false;

        std::sort(sink_.begin(), sink_.end());
        if (sink_.front() != 0 || sink_.back() != sink_.size() - 1)
            return false;

        return true;
    }

private:
    void LogImpl(std::ostream &os)
    {
    }

    template <typename TFirst, typename ...TRest>
    void LogImpl(std::ostream &os, TFirst &&first, TRest &&...rest)
    {
        os << std::forward<TFirst>(first);
        LogImpl(os, std::forward<TRest>(rest)...);
    }

    ostream_t &os_;
    std::mutex osMutex_;

    Semaphore fullCount_;
    Semaphore emptyCount_;
    CircularBuffer<int> buffer_;
    std::mutex bufferMutex_;

    std::size_t totalSize_;
    std::vector<int> sink_;
    std::mutex sinkMutex_;

    bool enableLogging_;
};


class Producer
{
public:
    Producer(ProducerConsumerContext &context, int start, int total, int bufferSize)
        : isThreadCreated_(false), context_(context), start_(start), total_(total), data_(bufferSize)
    {
    }

    std::thread Create()
    {
        if (isThreadCreated_)
            throw std::runtime_error("Thread already created.");

        isThreadCreated_ = true;

        return std::thread(
            [=]
        {
            std::size_t count;

            while (total_ > 0)
            {
                if (total_ >= static_cast<int>(data_.size()))
                {
                    std::iota(data_.begin(), data_.end(), start_);
                    count = static_cast<std::size_t>(data_.size());
                    context_.Produce(data_.data(), count);
                    start_ += static_cast<int>(count);
                    total_ -= static_cast<int>(count);
                }
                else
                {
                    std::iota(data_.begin(), data_.end(), start_);
                    count = total_;
                    context_.Produce(data_.data(), count);
                    start_ += static_cast<int>(count);
                    total_ -= static_cast<int>(count);
                }
            }

            context_.Log("Producer done!\n");
        }
        );
    }

private:
    bool isThreadCreated_;
    ProducerConsumerContext &context_;
    int start_;
    int total_;
    std::vector<int> data_;
};


class Consumer
{
public:
    Consumer(ProducerConsumerContext &context, int total, int bufferSize)
        : isThreadCreated_(false), context_(context), total_(total), data_(bufferSize)
    {
    }

    std::thread Create()
    {
        if (isThreadCreated_)
            throw std::runtime_error("Thread already created.");

        isThreadCreated_ = true;

        return std::thread(
            [=]
        {
            using namespace std::chrono_literals;
            
            size_t count;

            while (total_ > 0)
            {
                if (total_ >= static_cast<int>(data_.size()))
                {
                    count = static_cast<std::size_t>(data_.size());
                    context_.Consume(data_.data(), count);
                    context_.SaveData(data_.data(), count);
                    total_ -= static_cast<int>(count);
                }
                else
                {
                    count = total_;
                    context_.Consume(data_.data(), count);
                    context_.SaveData(data_.data(), count);
                    total_ -= count;
                }

                //std::this_thread::sleep_for(50ms);
            }

            context_.Log("\tConsumeer done!\n");
        }
        );
    }

private:
    bool isThreadCreated_;
    ProducerConsumerContext &context_;
    int total_;
    std::vector<int> data_;
};


void Test0()
{
    DIVIDING_LINE_1('-');

#if !PRODUCER_DO_MY_BEST && !CONSUMER_DO_MY_BEST
# error You are in danger of deadlock!
#endif

    constexpr int Count = 2000;

#if HAS_BOOST
    boost::recursive_mutex osMutex;
    ostream_t os(std::cout, osMutex);
#else
    ostream_t &os = std::cout;
#endif

    Stopwatch sw;
    sw.Start();

    ProducerConsumerContext context(os, Count, Count / 10, ENABLE_LOGGING);

    Producer p1(context, 0, Count / 2, 200);
    Producer p2(context, Count / 2, Count - Count / 2, 200);

    Consumer c1(context, Count / 3, 200);
    Consumer c2(context, Count / 3, 200);
    Consumer c3(context, Count - Count / 3 - Count / 3, 200);

    std::vector<std::thread> threads;
    threads.push_back(p1.Create());
    threads.push_back(p2.Create());
    threads.push_back(c1.Create());
    threads.push_back(c2.Create());
    threads.push_back(c3.Create());

    for (auto &t : threads)
        t.join();

    sw.Stop();

    std::cout << "Test Done: " << context.IsTestPassed() << ". Ellapsed time: " << sw.GetElapsedMilliseconds() << "ms\n";
}


void Test1()
{
    DIVIDING_LINE_1('-');

    constexpr int Count = 2001001;

#if HAS_BOOST
    boost::recursive_mutex osMutex;
    ostream_t os(std::cout, osMutex);
#else
    ostream_t &os = std::cout;
#endif

    Stopwatch sw;
    sw.Start();

    ProducerConsumerContext context(os, Count, Count / 10, ENABLE_LOGGING);

    Producer p1(context, 0, Count / 2, 200);
    Producer p2(context, Count / 2, Count - Count / 2, 200);

    Consumer c1(context, Count / 3, 200);
    Consumer c2(context, Count / 3, 200);
    Consumer c3(context, Count - Count / 3 - Count / 3, 200);

    std::vector<std::thread> threads;
    threads.push_back(p1.Create());
    threads.push_back(p2.Create());
    threads.push_back(c1.Create());
    threads.push_back(c2.Create());
    threads.push_back(c3.Create());

    for (auto &t : threads)
        t.join();

    sw.Stop();
    std::cout << "Ellapsed time: " << sw.GetElapsedMilliseconds() << "ms" << std::endl;

    std::cout << "Checking if test is passed...\n";

    sw.Restart();
    bool ok = context.IsTestPassed();
    sw.Stop();

    std::cout << "It takes " << sw.GetElapsedMilliseconds() << "ms to figure out if test is passed." << std::endl;
    std::cout << "Is test passed? " << std::boolalpha << ok << std::endl;
}


int main()
{
    Test0();
    PAUSE();

    Test1();
    PAUSE();

    return 0;
}


// References:
// https://en.wikipedia.org/wiki/Producer%96consumer_problem
// https://en.wikipedia.org/wiki/Monitor_(synchronization)
// C++ Concurrency in Action
// Ongoing-Study/c/PThreads/producer_consumer
// https://stackoverflow.com/questions/10673585/start-thread-with-member-function
// https://stackoverflow.com/questions/7231351/initializer-list-constructing-a-vector-of-noncopyable-but-movable-objects
// https://github.com/PacktPublishing/Cpp-High-Performance/blob/master/Chapter10/producer_consumer.cpp
// https://stackoverflow.com/questions/6/374264/is-cout-synchronized-thread-safe
// Ongoing-Study/cpp/C++11/varadic_template_test
// http://pages.cs.wisc.edu/~remzi/OSTEP/threads-cv.pdf
