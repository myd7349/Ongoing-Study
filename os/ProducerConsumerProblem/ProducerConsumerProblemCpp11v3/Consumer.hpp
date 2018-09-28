#pragma once

#include <algorithm>
#include <chrono>
#include <stdexcept>
#include <thread>
#include <vector>

#include "ConsumerContext.hpp"
#include "ProducerConsumerContextBase.hpp"


class Consumer
{
public:
    Consumer(ProducerConsumerContextBase &context, ConsumerContext &consumerContext, int total, int bufferSize)
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
            using namespace std::chrono_literals;

            std::size_t count;

            while (total_ > 0)
            {
                count = std::min<std::size_t>(data_.size(), total_);
                context_.Consume(data_.data(), count);
                std::reverse(data_.begin(), data_.begin() + count);
                consumerContext_.SaveData(data_.data(), count);
                total_ -= static_cast<int>(count);

                //std::this_thread::sleep_for(5ms);
            }

            context_.Log("\tConsumer done!\n");
        }
        );
    }

private:
    bool isThreadCreated_;
    ProducerConsumerContextBase &context_;
    ConsumerContext &consumerContext_;
    int total_;
    std::vector<int> data_;
};
