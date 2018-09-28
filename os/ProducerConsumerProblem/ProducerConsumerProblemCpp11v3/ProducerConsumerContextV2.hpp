#pragma once

#include <cassert>
#include <cstddef>
#include <iosfwd>
#include <mutex>

#include "../../../cpp/C++11/semaphore.hpp"
#include "ProducerConsumerContextBase.hpp"


#define PROTECT_BUFFER (1)

#define PRODUCER_DO_MY_BEST (0)
#define CONSUMER_DO_MY_BEST (0)


class ProducerConsumerContextV2 final : public ProducerConsumerContextBase
{
public:
    ProducerConsumerContextV2(std::size_t bufferSize, std::ostream &os, bool enableLogging)
        : ProducerConsumerContextBase(bufferSize, os, enableLogging),
        fillCount_(0), emptyCount_(static_cast<int>(bufferSize))
    {
    }

    void Produce(const int *items, std::size_t &count) override
    {
        assert(count <= buffer_.Capacity());

        Log("Producer is trying to get the lock...\n");

#if PRODUCER_DO_MY_BEST
        int slots = static_cast<int>(count);
        int timeout = 0;

        while (!emptyCount_.TryAcquire(slots, timeout))
        {
            if (slots > 1)
                slots -= 1;
            else
                timeout = -1;
        }

        count = static_cast<std::size_t>(slots);
#else
        emptyCount_.Acquire(count);
#endif

        {
            Log("Producer gets the lock...\n");

#if PROTECT_BUFFER
            std::unique_lock<std::mutex> lock(bufferMutex_);
#endif
            assert(ValidateSize());
            buffer_.PushBackMany(items, count);

            Log("Produce ", count, " items.\n");
        }

        fillCount_.Release(count);
    }

    void Consume(int *items, std::size_t &count) override
    {
        assert(count <= buffer_.Capacity());

        Log("\tConsumer is trying to get the lock...\n");

#if CONSUMER_DO_MY_BEST
        int slots = static_cast<int>(count);
        int timeout = 0;

        while (!fullCount_.TryAcquire(slots, timeout))
        {
            if (slots > 1)
                slots -= 1;
            else
                timeout = -1;
        }

        count = static_cast<std::size_t>(slots);
#else
        fillCount_.Acquire(count);
#endif

        {
            Log("\tConsumer gets the lock...\n");

#if PROTECT_BUFFER
            std::unique_lock<std::mutex> lock(bufferMutex_);
#endif
            assert(ValidateSize());
            buffer_.PopFrontMany(items, count);

            Log("\tConsume ", count, " items.\n");
        }

        emptyCount_.Release(count);
    }

private:
    Semaphore fillCount_;
    Semaphore emptyCount_;
    std::mutex bufferMutex_;
};


// References:
// [0] http://pages.cs.wisc.edu/~remzi/OSTEP/threads-cv.pdf
