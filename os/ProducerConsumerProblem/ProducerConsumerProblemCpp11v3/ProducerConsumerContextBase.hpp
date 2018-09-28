#pragma once

#include <cstddef>
#include <mutex>
#include <sstream>
#include <thread>
#include <utility>

#include "../../../cpp/common.h"
#include "../../../cpp/C++11/circular_buffer.hpp"
#include "../../../cpp/C++11/logger.hpp"


class NOVTABLE ProducerConsumerContextBase
{
public:
    ProducerConsumerContextBase(std::size_t bufferSize, std::ostream &os, bool enableLogging)
        : buffer_(bufferSize), os_(os), enableLogging_(enableLogging)
    {
    }

    template <typename ...TParams>
    void Log(TParams &&...params)
    {
        if (!enableLogging_)
            return;

        std::unique_lock<std::mutex> lock(osMutex_);

        std::ostringstream oss;
        oss << "[" << std::this_thread::get_id() << "]\t[" << buffer_.Size() << "]\t";
        ::Log(oss, std::forward<TParams>(params)...);
        os_ << oss.str();
    }

    virtual void Produce(const int *items, std::size_t &count) = 0;
    virtual void Consume(int *items, std::size_t &count) = 0;

protected:
    bool ValidateSize()
    {
        auto size = buffer_.Size();
        auto size2 = size;

        auto head = buffer_.Head();
        auto tail = buffer_.Tail();

        if (tail > head)
            size2 = tail - head;
        else if (tail < head)
            size2 = buffer_.Capacity() + tail - head;

        return size == size2;
    }

    CircularBuffer<int> buffer_;

private:
    std::ostream &os_;
    std::mutex osMutex_;
    bool enableLogging_;
};
