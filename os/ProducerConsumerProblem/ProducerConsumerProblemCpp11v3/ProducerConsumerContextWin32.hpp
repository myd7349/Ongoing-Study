#pragma once

#ifndef _WIN32
# error Win32 only!
#endif

#include <cassert>
#include <cstddef>
#include <iosfwd>

#define CRITICAL_SECTION_HEADER_ONLY
#include "../../../cpp/Win32/SDK/CriticalSection.h"

#define SRWLOCK_HEADER_ONLY
#include "../../../cpp/Win32/SDK/SRWLock.h"

#include "../../../cpp/Win32/SDK/ConditionVariable.hpp"
#include "../../../cpp/Win32/SDK/SingleLock.h"

#include "ProducerConsumerContextBase.hpp"


template <typename MutexT>
class ProducerConsumerContextWin32 final : public ProducerConsumerContextBase
{
public:
    ProducerConsumerContextWin32(std::size_t bufferSize, std::ostream &os, bool enableLogging)
        : ProducerConsumerContextBase(bufferSize, os, enableLogging)
    {
    }

    void Produce(const int *items, std::size_t &count) override
    {
        assert(count <= buffer_.Capacity());

        Log("Producer is trying to get the lock...\n");

        SingleLock<decltype(mutex_)> lock(mutex_);
        while (buffer_.Full())
            empty_.Wait(lock);

        count = std::min<std::size_t>(count, buffer_.Reserve());

        Log("Producer gets the lock...\n");

        assert(ValidateSize());
        buffer_.PushBackMany(items, count);

        Log("Produce ", count, " items.\n");

        fill_.NotifyOne();
    }

    void Consume(int *items, std::size_t &count) override
    {
        assert(count <= buffer_.Capacity());

        Log("\tConsumer is trying to get the lock...\n");

        SingleLock<decltype(mutex_)> lock(mutex_);
        while (buffer_.Empty())
            fill_.Wait(lock);

        count = std::min<std::size_t>(count, buffer_.Size());

        Log("\tConsumer gets the lock...\n");

        assert(ValidateSize());
        buffer_.PopFrontMany(items, count);

        Log("\tConsume ", count, " items.\n");

        empty_.NotifyOne();
    }

private:
    MutexT mutex_;
    ConditionVariable empty_;
    ConditionVariable fill_;
};


// References:
// [0] http://pages.cs.wisc.edu/~remzi/OSTEP/threads-cv.pdf
// Operating Systems: Three Easy Pieces, P352
