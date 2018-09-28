#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iosfwd>
#include <condition_variable>
#include <mutex>

#include "ProducerConsumerContextBase.hpp"


// See [0]
// Operating Systems: Three Easy Pieces, P348
// >With just a single producer and a single consumer, the code in Figure 30.6 works.
class ProducerConsumerContextV1 final : public ProducerConsumerContextBase
{
public:
    ProducerConsumerContextV1(std::size_t bufferSize, std::ostream &os, bool enableLogging)
        : ProducerConsumerContextBase(bufferSize, os, enableLogging)
    {
    }

    void Produce(const int *items, std::size_t &count) override
    {
        assert(count <= buffer_.Capacity());

        Log("Producer is trying to get the lock...\n");

        std::unique_lock<std::mutex> lock(mutex_);
        if (buffer_.Full())
            cond_.wait(lock);

        count = std::min<std::size_t>(count, buffer_.Reserve());

        Log("Producer gets the lock...\n");

        assert(ValidateSize());
        buffer_.PushBackMany(items, count);

        Log("Produce ", count, " items.\n");

        cond_.notify_one();
    }

    void Consume(int *items, std::size_t &count) override
    {
        assert(count <= buffer_.Capacity());

        Log("\tConsumer is trying to get the lock...\n");

        std::unique_lock<std::mutex> lock(mutex_);
        if (buffer_.Empty())
            cond_.wait(lock);

        count = std::min<std::size_t>(count, buffer_.Size());

        Log("\tConsumer gets the lock...\n");

        assert(ValidateSize());
        buffer_.PopFrontMany(items, count);

        Log("\tConsume ", count, " items.\n");

        cond_.notify_one();
    }

private:
    std::mutex mutex_;
    std::condition_variable cond_;
};


// References:
// [0] http://pages.cs.wisc.edu/~remzi/OSTEP/threads-cv.pdf
