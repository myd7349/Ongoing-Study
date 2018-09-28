#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "ProducerConsumerContextBase.hpp"


class ProducerConsumerContextWin32V2 final : public ProducerConsumerContextBase
{
public:
    typedef std::vector<int>::size_type SizeType;

    ProducerConsumerContextWin32V2(SizeType bufferSize, std::ostream &os, bool enableLogging)
        : ProducerConsumerContextBase(bufferSize, os, enableLogging)
        , buffer_(bufferSize)
        , fillPtr_(0), usePtr_(0), size_(0)
    {
        InitializeCriticalSectionEx(&mutex_, 4000, 0);

        InitializeConditionVariable(&empty_);
        InitializeConditionVariable(&fill_);
    }

    ~ProducerConsumerContextWin32V2()
    {
        DeleteCriticalSection(&mutex_);
    }

    void Produce(const int *items, std::size_t &count) override
    {
        Log("Producer is trying to get the lock...\n");

        EnterCriticalSection(&mutex_);

        while (size_ == buffer_.size())
            SleepConditionVariableCS(&empty_, &mutex_, INFINITE);

        Log("Producer gets the lock...\n");

        Put(items, count);

        Log("Produce ", count, " items.\n");

        WakeConditionVariable(&fill_);

        LeaveCriticalSection(&mutex_);
    }

    void Consume(int *items, std::size_t &count) override
    {
        Log("\tConsumer is trying to get the lock...\n");

        EnterCriticalSection(&mutex_);

        while (size_ == 0)
            SleepConditionVariableCS(&fill_, &mutex_, INFINITE);

        Log("\tConsumer gets the lock...\n");

        Get(items, count);
        std::reverse(items, items + count);

        Log("\tConsume ", count, " items.\n");

        WakeConditionVariable(&empty_);

        LeaveCriticalSection(&mutex_);
    }

private:
    __forceinline void Put(const int *data, std::size_t &count)
    {
        assert(fillPtr_ < buffer_.size());
        assert(size_ < buffer_.size());

        auto reserved = buffer_.size() - size_;
        if (count > reserved)
            count = reserved;

        if (fillPtr_ <=  buffer_.size() - count)
        {
            std::copy(data, data + count, buffer_.begin() + fillPtr_);
        }
        else
        {
            auto emptySlotsAtEnd = buffer_.size() - fillPtr_;
            auto emptySlotsAtBegin = count - emptySlotsAtEnd;

            std::copy(data, data + emptySlotsAtEnd, buffer_.end() - emptySlotsAtEnd);
            std::copy(data + emptySlotsAtEnd, data + count, buffer_.begin());
        }

        size_ += count;
        fillPtr_ = (fillPtr_ + count) % buffer_.size();
    }

    __forceinline void Get(int *data, std::size_t &count)
    {
        assert(usePtr_ < buffer_.size());
        assert(size_ > 0);

        if (count > size_)
            count = size_;

        if (usePtr_ <=  buffer_.size() - count)
        {
            std::copy(buffer_.cbegin() + usePtr_, buffer_.cbegin() + usePtr_ + count, data);
        }
        else
        {
            auto filledSlotsAtEnd = buffer_.size() - usePtr_;
            auto filledSlotsAtBegin = count - filledSlotsAtEnd;

            std::copy(buffer_.cend() - filledSlotsAtEnd, buffer_.cend(), data);
            std::copy(buffer_.cbegin(), buffer_.cbegin() + filledSlotsAtBegin, data + filledSlotsAtEnd);
        }

        size_ -= count;
        usePtr_ = (usePtr_ + count) % buffer_.size();
    }

    std::vector<int> buffer_;
    SizeType fillPtr_;
    SizeType usePtr_;
    SizeType size_;

    CRITICAL_SECTION mutex_;
    CONDITION_VARIABLE empty_;
    CONDITION_VARIABLE fill_;
};


// References:
// [0] http://pages.cs.wisc.edu/~remzi/OSTEP/threads-cv.pdf
// Operating Systems: Three Easy Pieces, P352
// https://docs.microsoft.com/zh-cn/windows/desktop/Sync/condition-variables
