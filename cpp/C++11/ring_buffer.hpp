#ifndef RING_BUFFER_HPP_
#define RING_BUFFER_HPP_

#include <atomic>
#include <cstddef>


template <typename T, std::size_t Size>
class NonThreadSafeRingBuffer
{
public:
    NonThreadSafeRingBuffer()
        : head_(0), tail_(0)
    {
    }

    bool Push(T value)
    {
        std::size_t next_head = Next_(head_);
        if (next_head == tail_)
            return false;

        buffer_[head_] = value;
        head_ = next_head;
        return true;
    }

    bool Pop(T &value)
    {
        if (tail_ == head_)
            return false;

        value = buffer_[tail_];
        tail_ = Next_(tail_);
        return true;
    }

private:
    std::size_t Next_(std::size_t current)
    {
        return (current + 1) % Size;
    }

    std::size_t head_;
    std::size_t tail_;
    T buffer_[Size];
};


template <typename T, std::size_t Size>
class WaitFreeRingBuffer
{
public:
    WaitFreeRingBuffer()
        : head_(0), tail_(0)
    {
    }

    bool Push(T value)
    {
        std::size_t head = head_.load(std::memory_order_relaxed);
        std::size_t next_head = Next_(head);
        if (next_head == tail_.load(std::memory_order_acquire))
            return false;

        buffer_[head] = value;
        head_.store(next_head, std::memory_order_release);
        return true;
    }

    bool Pop(T &value)
    {
        std::size_t tail = tail_.load(std::memory_order_relaxed);
        if (tail == head_.load(std::memory_order_acquire))
            return false;

        value = buffer_[tail];
        tail_.store(Next_(tail), std::memory_order_release);
        return true;
    }

private:
    std::size_t Next_(std::size_t current)
    {
        return (current + 1) % Size;
    }

    std::atomic<std::size_t> head_;
    std::atomic<std::size_t> tail_;
    T buffer_[Size];
};

#endif // RING_BUFFER_HPP_


// References:
// https://www.boost.org/doc/libs/1_65_1/doc/html/atomic/usage_examples.html#boost_atomic.usage_examples.example_ringbuffer
