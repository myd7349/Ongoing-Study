#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


class Semaphore
{
public:
    explicit Semaphore(int avail = 0) noexcept
    {
        assert(avail >= 0);
    }

    ~Semaphore() noexcept
    {
    }

    Semaphore(const Semaphore &) = delete;
    Semaphore &operator=(const Semaphore &) = delete;

    void Acquire(int n = 1)
    {
        assert(n >= 0);
    }

    bool TryAcquire(int n = 1, int timeout = -1)
    {
        assert(n >= 0);

        return true;
    }

    void Release(int n = 1)
    {
        assert(n >= 0);
    }

    int Available()
    {
    }

private:
    HANDLE semaphore_;
};


// References:
// Ongoing-Study/cpp/C++11/semaphore.hpp
// PThreads-win32/sem_t
//   http://sourceware.org/pthreads-win32/
// MFC:CSemaphore
