#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "ProducerConsumerContextBase.hpp"


template <typename T>
class ProducerConsumerContextWin32 final : public ProducerConsumerContextBase<T>
{
public:
    ProducerConsumerContextWin32(SizeType bufferSize, std::ostream &os, bool enableLogging)
        : ProducerConsumerContextBase(bufferSize, os, enableLogging)
    {
        InitializeCriticalSectionEx(&mutex_, 4000, 0);

        InitializeConditionVariable(&empty_);
        InitializeConditionVariable(&fill_);
    }

    ~ProducerConsumerContextWin32()
    {
        DeleteCriticalSection(&mutex_);
    }

    void Produce(const T *items, SizeType &count) override
    {
        assert(items != nullptr);
        assert(count <= buffer_.Capacity());

        Log("Producer is trying to get the lock...\n");

        EnterCriticalSection(&mutex_);

        while (buffer_.IsFull())
            SleepConditionVariableCS(&empty_, &mutex_, INFINITE);

        Log("Producer gets the lock...\n");

        buffer_.Push(items, count);

        Log("Produce ", count, " items.\n");

        WakeConditionVariable(&fill_);

        LeaveCriticalSection(&mutex_);
    }

    void Consume(T *items, SizeType &count) override
    {
        assert(items != nullptr);
        assert(count <= buffer_.Capacity());

        Log("\tConsumer is trying to get the lock...\n");

        EnterCriticalSection(&mutex_);

        while (buffer_.IsEmpty())
            SleepConditionVariableCS(&fill_, &mutex_, INFINITE);

        Log("\tConsumer gets the lock...\n");

        buffer_.Pull(items, count);

        Log("\tConsume ", count, " items.\n");

        WakeConditionVariable(&empty_);

        LeaveCriticalSection(&mutex_);
    }

private:
    CRITICAL_SECTION mutex_;
    CONDITION_VARIABLE empty_;
    CONDITION_VARIABLE fill_;
};


// References:
// http://pages.cs.wisc.edu/~remzi/OSTEP/threads-cv.pdf
// Operating Systems: Three Easy Pieces, P352
// https://docs.microsoft.com/zh-cn/windows/desktop/Sync/condition-variables
