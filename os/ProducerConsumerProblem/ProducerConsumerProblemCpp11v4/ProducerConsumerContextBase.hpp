#pragma once

#include <mutex>
#include <sstream>
#include <thread>
#include <utility>

#include "../../../cpp/C++11/logger.hpp"
#include "CircularBuffer.hpp"


template <typename T>
class ProducerConsumerContextBase
{
public:
    typedef typename CircularBuffer<T>::SizeType SizeType;
    typedef typename CircularBuffer<T>::ValueType ValueType;

    ProducerConsumerContextBase(SizeType bufferSize, std::ostream &os, bool enableLogging)
        : buffer_(bufferSize), os_(os), enableLogging_(enableLogging)
    {
    }

    virtual ~ProducerConsumerContextBase() = default;

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

    virtual void Produce(const T *items, SizeType &count) = 0;
    virtual void Consume(T *items, SizeType &count) = 0;

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

    CircularBuffer<T> buffer_;

private:
    std::ostream &os_;
    std::mutex osMutex_;
    bool enableLogging_;
};
