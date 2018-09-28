#pragma once

#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <thread>
#include <vector>

#include "ProducerConsumerContextBase.hpp"


template <typename T>
class Producer
{
public:
    typedef typename ProducerConsumerContextBase<T>::SizeType SizeType;

    Producer(ProducerConsumerContextBase<T> &context, SizeType start, SizeType total, SizeType bufferSize)
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
            while (total_ > 0)
            {
                auto count = std::min<SizeType>(data_.size(), total_);
                std::iota(data_.begin(), data_.end(), start_);
                context_.Produce(data_.data(), count);
                start_ += count;
                total_ -= count;
            }

            context_.Log("Producer done!\n");
        }
        );
    }

private:
    bool isThreadCreated_;
    ProducerConsumerContextBase<T> &context_;
    SizeType start_;
    SizeType total_;
    std::vector<T> data_;
};
