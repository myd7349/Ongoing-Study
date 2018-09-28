#pragma once

#include <algorithm>
#include <cassert>
#include <mutex>
#include <vector>

#include "../../../cpp/C++11/is_unique.hpp"


template <typename T>
class ConsumerContext
{
public:
    typedef typename std::vector<T>::size_type SizeType;

    ConsumerContext(SizeType totalSize, bool multipleConsumers)
        : totalSize_(totalSize), multipleConsumers_(multipleConsumers)
    {
        sink_.reserve(totalSize_);
    }

    void SaveData(T *items, SizeType count)
    {
        assert(items != nullptr);

        if (multipleConsumers_)
        {
            std::unique_lock<std::mutex> lock(mutex_);
            std::copy(items, items + count, std::back_inserter(sink_));
        }
        else
        {
            std::copy(items, items + count, std::back_inserter(sink_));
        }
    }

    bool IsTestPassed()
    {
        if (sink_.size() != totalSize_)
            return false;

        if (sink_.front() != T() || sink_.back() != sink_.size() - 1)
            return false;

        if (!is_unique_impl_using_sort(sink_.begin(), sink_.end()))
            return false;

        return true;
    }

private:
    SizeType totalSize_;
    const bool multipleConsumers_;

    std::vector<T> sink_;
    std::mutex mutex_;
};
