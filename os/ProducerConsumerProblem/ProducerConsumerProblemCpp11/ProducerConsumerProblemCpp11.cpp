// 2018-02-11T13:30+08:00
#include <algorithm>
#include <assert.h>
#include <atomic>
#include <deque>
#include <iostream>
#include <limits>
#include <thread>
#include <unordered_set>

#include "../../../c/clog.h"
#include "../../../cpp/C++11/semaphore.hpp"


#define ENABLE_LOGGING 0

#if ENABLE_LOGGING
# define LOG(fmt, ...) INFO(fmt, __VA_ARGS__)
#else
# define LOG(fmt, ...) ((void)0)
#endif


class ProducerConsumerProblem
{
public:
    ProducerConsumerProblem(int bufferSize)
        : buffer_(bufferSize), fillCount_(0), emptyCount_(bufferSize)
        , producerTurns_(bufferSize)
        , consumerTurns_(bufferSize)
        , current_(0)
    {
    }

    void Produce(int start, int count)
    {
        for (int i = 0; i < count; ++i)
        {
            emptyCount_.Acquire();

            {
                LOG("Producer:: Put a new item into buffer.");

                std::unique_lock<std::mutex> lock(mutex_);
                buffer_[current_++] = start++;
            }

            fillCount_.Release();
        }
    }

    void Consume(int count)
    {
        for (int i = 0; i < count; ++i)
        {
            fillCount_.Acquire();

            {
                LOG("Consumer:: Pull a item from buffer.");

                std::unique_lock<std::mutex> lock(mutex_);
                data_.push_back(buffer_[--current_]);
                if (data_.size() == buffer_.size())
                {
                    emptyCount_.Release();
                    break;
                }
            }

            emptyCount_.Release();
        }
    }

    bool IsTestPassed()
    {
        if (data_.size() != buffer_.size())
            return false;

        std::unordered_set<int> set(data_.cbegin(), data_.cend());
        if (set.size() != buffer_.size())
            return false;

        std::sort(data_.begin(), data_.end());
        if (data_.front() != 0 || data_.back() != data_.size() - 1)
            return false;

        if (current_ != 0)
            return false;

        return true;
    }


private:
    std::deque<int> buffer_;
    std::deque<int>::size_type current_;
    std::deque<int> data_;
    std::mutex mutex_;
    Semaphore fillCount_;
    Semaphore emptyCount_;
    std::atomic_int producerTurns_;
    std::atomic_int consumerTurns_;
};


int main()
{
    const int Count = 2001001;

    ProducerConsumerProblem problem(Count);

    std::deque<std::thread> threads;
    {
        threads.push_back(std::thread(&ProducerConsumerProblem::Produce, &problem, 0, Count / 2));
        threads.push_back(std::thread(&ProducerConsumerProblem::Produce, &problem, Count / 2, Count - Count / 2));
        threads.push_back(std::thread(&ProducerConsumerProblem::Consume, &problem, Count / 3));
        threads.push_back(std::thread(&ProducerConsumerProblem::Consume, &problem, Count / 3));
        threads.push_back(std::thread(&ProducerConsumerProblem::Consume, &problem, Count - Count / 3 - Count / 3));
    }

    for (auto &t : threads)
        t.join();

    std::cout << "Test Done: " << problem.IsTestPassed() << std::endl;

    std::getchar();

    return 0;
}


// References:
// https://en.wikipedia.org/wiki/Producer%96consumer_problem
// https://en.wikipedia.org/wiki/Monitor_(synchronization)
// C++ Concurrency in Action
// Ongoing-Study/c/PThreads/producer_consumer
// https://stackoverflow.com/questions/10673585/start-thread-with-member-function
// https://stackoverflow.com/questions/7231351/initializer-list-constructing-a-vector-of-noncopyable-but-movable-objects
