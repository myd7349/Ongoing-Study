#pragma once

#include <algorithm>
#include <cstddef>
#include <mutex>
#include <vector>

#include "../../../cpp/C++11/is_unique.hpp"


class ConsumerContext
{
public:
    ConsumerContext(std::size_t totalSize, bool multipleConsumers)
        : totalSize_(totalSize), multipleConsumers_(multipleConsumers)
    {
        sink_.reserve(totalSize_);
    }

    void SaveData(int *items, std::size_t count)
    {
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

        if (sink_.front() != 0 || sink_.back() != sink_.size() - 1)
            return false;

        if (!is_unique_impl_using_sort(sink_.begin(), sink_.end()))
            return false;

        return true;
    }

private:
    std::size_t totalSize_;
    const bool multipleConsumers_;

    std::vector<int> sink_;
    std::mutex mutex_;
};
