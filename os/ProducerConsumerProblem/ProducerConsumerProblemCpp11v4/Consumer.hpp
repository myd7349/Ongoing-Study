#pragma once

#include <chrono>
#include <stdexcept>
#include <thread>
#include <vector>

#include "ConsumerContext.hpp"
#include "ProducerConsumerContextBase.hpp"


template <typename T>
class Consumer
{
public:
    typedef typename ProducerConsumerContextBase<T>::SizeType SizeType;

    Consumer(ProducerConsumerContextBase<T> &context, ConsumerContext<T> &consumerContext, SizeType total, SizeType bufferSize)
        : isThreadCreated_(false), context_(context), consumerContext_(consumerContext), total_(total), data_(bufferSize)
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
                context_.Consume(data_.data(), count);
                consumerContext_.SaveData(data_.data(), count);
                total_ -= count;

                using namespace std::chrono_literals;
                //std::this_thread::sleep_for(5ms);
            }

            context_.Log("\tConsumer done!\n");
        }
        );
    }

private:
    bool isThreadCreated_;
    ProducerConsumerContextBase<T> &context_;
    ConsumerContext<T> &consumerContext_;
    SizeType total_;
    std::vector<T> data_;
};
