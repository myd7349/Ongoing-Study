#pragma once

#include <cassert>
#include <cstddef>
#include <stdexcept>
#include <vector>


template <typename T>
class CircularBuffer
{
public:
    typedef typename std::vector<T>::size_type SizeT;

    CircularBuffer(SizeT n)
        : buffer_(n)
    {
    }

    SizeT Head() const noexcept
    {
        return head_;
    }

    SizeT Tail() const noexcept
    {
        return (head_ + size_) % Capacity();
    }

    SizeT Capacity() const noexcept
    {
        return buffer_.size();
    }

    SizeT Size() const noexcept
    {
        return size_;
    }

    bool Empty() const noexcept
    {
        return Size() == 0;
    }

    bool Full() const noexcept
    {
        return Size() == Capacity();
    }

    SizeT Reserve() const noexcept
    {
        return Capacity() - Size();
    }

    void PushFront(T item)
    {
        if (Full())
            throw std::out_of_range("Can't push items into a full buffer");

        head_ = Decrement_(head_);
        buffer_[head_] = item;
        size_ += 1;
    }

    void PushFrontMany(const T *items, SizeT count)
    {
        assert(items != nullptr);
        assert(count > 0);

        while (count > 0)
            PushFront(items[--count]);
    }

    void PushBack(T item)
    {
        if (Full())
            throw std::out_of_range("Can't push items into a full buffer");

        buffer_[tail_] = item;
        size_ += 1;
        tail_ = Increment_(tail_);
    }

    void PushBackMany(const T *items, SizeT count)
    {
        assert(items != nullptr);

        for (SizeT i = 0; i < count; ++i)
            PushBack(items[i]);
    }

    T PopFront()
    {
        if (Empty())
            throw std::out_of_range("Can't pull items from an empty buffer");

        T item = buffer_[head_];
        head_ = Increment_(head_);
        size_ -= 1;
        return item;
    }

    void PopFrontMany(T *items, SizeT count)
    {
        assert(items != nullptr);
        assert(count > 0);

        while (count > 0)
            items[--count] = PopFront();
    }

    T PopBack()
    {
        if (Empty())
            throw std::out_of_range("Can't pull items from an empty buffer");

        tail_ = Decrement_(tail_);
        T item = buffer_[tail_];
        size_ -= 1;
        return item;
    }

    void PopBackMany(T *items, SizeT count)
    {
        assert(items != nullptr);

        for (SizeT i = 0; i < count; ++i)
            items[i] = PopBack();
    }

    T &operator[](SizeT index)
    {
        if (index >= Size())
            throw std::out_of_range("Index out of range");

        index = head_ + index;
        if (index >= Capacity())
            index %= Capacity();

        return buffer_[index];
    }

    T operator[](SizeT index) const
    {
        if (index >= Size())
            throw std::out_of_range("Index out of range");

        index = head_ + index;
        if (index >= Capacity())
            index %= Capacity();

        return buffer_[index];
    }

private:
    SizeT Increment_(SizeT index) const
    {
        return (index + 1) % Capacity();
    }

    SizeT Decrement_(SizeT index) const
    {
        if (index == 0)
            index = Capacity();

        return --index;
    }

    std::vector<T> buffer_;
    SizeT head_ = 0;
    SizeT tail_ = 0;
    SizeT size_ = 0;
};


// References:
// https://en.wikipedia.org/wiki/Circular_buffer
// Boost.Circular_buffer
