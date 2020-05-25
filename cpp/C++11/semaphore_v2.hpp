// 2018-05-03T20:49+08:00
#ifndef SEMAPHORE_V2_HPP_
#define SEMAPHORE_V2_HPP_

#include <atomic>
#include <cassert>
#include <chrono>
#include <thread>


class SemaphoreV2
{
public:
    explicit SemaphoreV2(int avail = 0) noexcept
        : avail_(avail)
    {
        assert(avail_ >= 0);
    }

    ~SemaphoreV2() noexcept
    {
    }

    SemaphoreV2(const SemaphoreV2 &) = delete;
    
    SemaphoreV2 &operator=(const SemaphoreV2 &) = delete;    

    void Acquire(int n = 1)
    {

    }

    bool TryAcquire(int n = 1, int timeout = -1)
    {

    }

    void Release(int n = 1)
    {

    }

    int Available()
    {

    }

private:
    std::atomic_int avail_;
};

#endif // SEMAPHORE_V2_HPP_


// References:
// Modern Operating System, 4th Edition, P130, Ch2.3.5
// https://www.arangodb.com/2015/02/comparing-atomic-mutex-rwlocks/
// http://en.cppreference.com/w/cpp/atomic/atomic_fetch_and