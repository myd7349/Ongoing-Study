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
// [Lock-Free Single-Producer - Single Consumer Circular Queue](https://www.codeproject.com/Articles/43510/Lock-Free-Single-Producer-Single-Consumer-Circular)
// https://github.com/KjellKod/lock-free-wait-free-circularfifo
// [Why is a single-producer single-consumer circular queue thread safe without locking?](https://stackoverflow.com/questions/14142023/why-is-a-single-producer-single-consumer-circular-queue-thread-safe-without-lock)
// [c++ lock free queue implementation single producer single consumer](https://stackoverflow.com/questions/65463578/c-lock-free-queue-implementation-single-producer-single-consumer)
// > Debug builds will often "happen to work" especially on x86 because the constraints that puts on code-gen block compile-time reordering, and x86 hardware blocks most run-time reordering.
// https://www.drdobbs.com/cpp/lock-free-code-a-false-sense-of-security/210600279?pgno=1
// https://herbsutter.com/2008/08/05/effective-concurrency-lock-free-code-a-false-sense-of-security/
/*
Given that lock-based synchronization has serious problems [1], it can be tempting to think lock-free code must be the answer.
Sometimes that is true. In particular, it's useful to have libraries provide hash tables and other handy types whose implementations
are internally synchronized using lock-free techniques, such as Java's ConcurrentHashMap, so that we can use those types safely from 
multiple threads without external synchronization and without having to understand the subtle lock-free implementation details.

But replacing locks wholesale by writing your own lock-free code is not the answer. Lock-free code has two major drawbacks. First,
it's not broadly useful for solving typical problems—lots of basic data structures, even doubly linked lists, still have no known
lock-free implementations. Coming up with a new or improved lock-free data structure will still earn you at least a published paper
in a refereed journal, and sometimes a degree.

Second, it's hard even for experts. It's easy to write lock-free code that appears to work, but it's very difficult to write lock-free
code that is correct and performs well. Even good magazines and refereed journals have published a substantial amount of lock-free code
that was actually broken in subtle ways and needed correction.

To illustrate, let's dissect some peer-reviewed lock-free code that was published here in DDJ just two months ago [2]. The author,
Petru Marginean, has graciously allowed me to dissect it here so that we can see what's wrong and why, what lessons we should learn, and
how to write the code correctly. That someone as knowledgable as Petru, who has published many good and solid articles, can get this stuff
wrong should be warning enough that lock-free coding requires great care.
*/
// https://github.com/cameron314/readerwriterqueue
// [C++ lock free, single producer, single consumer queue](https://codereview.stackexchange.com/questions/219389/c-lock-free-single-producer-single-consumer-queue)
