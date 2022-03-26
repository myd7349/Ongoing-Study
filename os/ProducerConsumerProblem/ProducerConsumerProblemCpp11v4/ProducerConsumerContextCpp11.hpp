#pragma once

#include <cassert>
#include <condition_variable>
#include <iosfwd>
#include <mutex>


#include "ProducerConsumerContextBase.hpp"


template <typename T>
class ProducerConsumerContextCpp11 final : public ProducerConsumerContextBase<T>
{
public:
    ProducerConsumerContextCpp11(SizeType bufferSize, std::ostream &os, bool enableLogging)
        : ProducerConsumerContextBase(bufferSize, os, enableLogging)
    {
    }

    void Produce(const T *items, SizeType &count) override
    {
        assert(items != nullptr);
        assert(count <= buffer_.Capacity());

        Log("Producer is trying to get the lock...\n");

        std::unique_lock<std::mutex> lock(mutex_);
        while (buffer_.IsFull())
            empty_.wait(lock);

        Log("Producer gets the lock...\n");

        assert(ValidateSize());
        buffer_.Push(items, count);

        Log("Produce ", count, " items.\n");

        fill_.notify_one();
    }

    void Consume(T *items, SizeType &count) override
    {
        assert(items != nullptr);
        assert(count <= buffer_.Capacity());

        Log("\tConsumer is trying to get the lock...\n");

        std::unique_lock<std::mutex> lock(mutex_);
        while (buffer_.IsEmpty())
            fill_.wait(lock);

        Log("\tConsumer gets the lock...\n");

        assert(ValidateSize());
        buffer_.Pull(items, count);

        Log("\tConsume ", count, " items.\n");

        empty_.notify_one();
    }

private:
    std::mutex mutex_;
    std::condition_variable empty_;
    std::condition_variable fill_;
};


// References:
// http://pages.cs.wisc.edu/~remzi/OSTEP/threads-cv.pdf
// Operating Systems: Three Easy Pieces, P352
// https://github.com/samanbarghi/MPSCQ
