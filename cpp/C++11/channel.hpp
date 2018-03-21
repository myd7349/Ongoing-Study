// 2018-03-21T09:11+08:00
#ifndef CHANNEL_HPP_
#define CHANNEL_HPP_

#include <cassert>
#include <cstddef>
#include <cstring>

#include "semaphore.hpp"


class Channel
{
public:
    Channel() noexcept
        : send_(1), ptr_(nullptr), size_(nullptr)
    {
    }

    Channel(const Channel &) = delete;
    Channel &operator=(const Channel &) = delete;

    std::size_t Send(const void *ptr, std::size_t size)
    {
        assert(ptr != nullptr);

        send_.Acquire();

        ptr_ = ptr;
        size_ = &size;

        recv_.Release();

        sync_.Acquire();

        return size;
    }
    
    std::size_t Receive(void *ptr, std::size_t size)
    {
        assert(ptr != nullptr);

        recv_.Acquire();

        assert(ptr_ != nullptr);
        assert(size_ != nullptr);

        std::size_t n = *size_;
        if (size < n)
            n = size;
        *size_ = n;

        if (n > 0)
            std::memcpy(ptr, ptr_, n);

        sync_.Release();
        send_.Release();

        return n;
    }

private:
    Semaphore send_;
    Semaphore recv_;
    Semaphore sync_;

    const void *ptr_;
    std::size_t *size_;
};

#endif


// References:
// C Interfaces and Implementations: Techniques for Creating Reusable Software, by David R. Hanson, Chapter 20
// https://codereview.stackexchange.com/questions/32500/golang-channel-in-c
