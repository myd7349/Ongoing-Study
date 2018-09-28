#pragma once

#include <algorithm>
#include <cstddef>
#include <numeric>
#include <stdexcept>
#include <thread>
#include <vector>

#include "ProducerConsumerContextBase.hpp"


class Producer
{
public:
    Producer(ProducerConsumerContextBase &context, int start, int total, int bufferSize)
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
                count = std::min<std::size_t>(data_.size(), total_);
                std::iota(data_.begin(), data_.end(), start_);
                context_.Produce(data_.data(), count);
                start_ += static_cast<int>(count);
                total_ -= static_cast<int>(count);
            }

            context_.Log("Producer done!\n");
        }
        );
    }

private:
    bool isThreadCreated_;
    ProducerConsumerContextBase &context_;
    int start_;
    int total_;
    std::vector<int> data_;
};
