#pragma once

#include <algorithm>
#include <cassert>
#include <vector>


template <typename T>
class CircularBuffer
{
public:
    typedef typename std::vector<T>::size_type SizeType;
    typedef typename std::vector<T>::value_type ValueType;

    CircularBuffer(SizeType bufferSize)
        : buffer_(bufferSize)
        , fillPtr_(0), usePtr_(0), size_(0)
    {
    }

    void Push(const T *data, SizeType &count)
    {
        assert(data != nullptr);
        assert(fillPtr_ < buffer_.size());
        assert(size_ < buffer_.size());

        if (count > Reserve())
            count = Reserve();

        if (count == 0)
            return;

        if (fillPtr_ <= buffer_.size() - count)
        {
            std::copy(data, data + count, buffer_.begin() + fillPtr_);
        }
        else
        {
            auto emptySlotsAtEnd = buffer_.size() - fillPtr_;
            auto emptySlotsAtBegin = count - emptySlotsAtEnd;

            std::copy(data, data + emptySlotsAtEnd, buffer_.end() - emptySlotsAtEnd);
            std::copy(data + emptySlotsAtEnd, data + count, buffer_.begin());
        }

        size_ += count;
        fillPtr_ = (fillPtr_ + count) % buffer_.size();
    }

    void Pull(T *data, SizeType &count)
    {
        assert(data != nullptr);
        assert(usePtr_ < buffer_.size());
        assert(size_ > 0);

        if (count > size_)
            count = size_;

        if (count == 0)
            return;

        if (usePtr_ <= buffer_.size() - count)
        {
            std::copy(buffer_.cbegin() + usePtr_, buffer_.cbegin() + usePtr_ + count, data);
        }
        else
        {
            auto filledSlotsAtEnd = buffer_.size() - usePtr_;
            auto filledSlotsAtBegin = count - filledSlotsAtEnd;

            std::copy(buffer_.cend() - filledSlotsAtEnd, buffer_.cend(), data);
            std::copy(buffer_.cbegin(), buffer_.cbegin() + filledSlotsAtBegin, data + filledSlotsAtEnd);
        }

        size_ -= count;
        usePtr_ = (usePtr_ + count) % buffer_.size();
    }

    SizeType Capacity() const
    {
        return buffer_.size();
    }

    SizeType Size() const
    {
        return size_;
    }

    SizeType Reserve() const
    {
        return Capacity() - Size();
    }

    SizeType Head() const
    {
        return usePtr_;
    }

    SizeType Tail() const
    {
        return fillPtr_;
    }

    bool IsEmpty() const
    {
        return size_ == 0;
    }

    bool IsFull() const
    {
        return size_ == buffer_.size();
    }

private:
    std::vector<T> buffer_;
    SizeType fillPtr_;
    SizeType usePtr_;
    SizeType size_;
};


// References:
// http://pages.cs.wisc.edu/~remzi/OSTEP/threads-cv.pdf
// Operating Systems: Three Easy Pieces, P352
// https://github.com/michaeltyson/TPCircularBuffer
