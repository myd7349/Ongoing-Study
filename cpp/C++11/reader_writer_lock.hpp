// 2018-06-12T19:26+08:00
#ifndef READER_WRITER_LOCK_HPP_
#define READER_WRITER_LOCK_HPP_

#include "semaphore.hpp"


class ReaderPreferringReaderWriterLock
{
public:
    ReaderPreferringReaderWriterLock() noexcept
        : resourceMutex_(1)
    {
    }

    ReaderPreferringReaderWriterLock(const ReaderPreferringReaderWriterLock &) = delete;
    ReaderPreferringReaderWriterLock &operator=(const ReaderPreferringReaderWriterLock &) = delete;

    void AcquireReaderLock()
    {
        std::unique_lock<std::mutex> lock(readCountMutex_);
        readCount_ += 1;
        if (readCount_ == 1)
            resourceMutex_.Acquire();
    }

    void ReleaseReaderLock()
    {
        std::unique_lock<std::mutex> lock(readCountMutex_);
        readCount_ -= 1;
        if (readCount_ == 0)
            resourceMutex_.Release();
    }

    void AcquireWriterLock()
    {
        resourceMutex_.Acquire();
    }

    void ReleaseWriterLock()
    {
        resourceMutex_.Release();
    }
    
    //void ReleaseLock();

    //bool AnyWritersSince(int sequence);
    //bool IsReaderLockHeld() const;
    //bool IsWriterLockHeld() const;
    //int GetWriterSequenceNumber() const;

private:
    int readCount_ = 0;
    std::mutex readCountMutex_;
    // Note: we can not use std::mutex here.
    // Multithreading applications in Win32, Chapter 7
    // >The problem is that the first reader to get the lock is 
    //  not necessarily the last reader to leave. Therefore one
    //  thread would lock the mutex and another thread would try
    //  to release it. With Win32 mutexes, this is illegal. I changed
    //  the implementation to make hDataLock a semaphore instead
    //  because semaphores can be locked and released by any thread.
    //  The semaphore has a maximum count of one and an initial value
    //  of one, meaning that it starts out unowned and a grand total of
    //  one thread can lock it.
    Semaphore resourceMutex_;
};


class WriterPreferringReaderWriterLock
{
public:
    WriterPreferringReaderWriterLock() noexcept
        : readTryMutex_(1), resourceMutex_(1)
    {
    }

    WriterPreferringReaderWriterLock(const WriterPreferringReaderWriterLock &) = delete;
    WriterPreferringReaderWriterLock &operator=(const WriterPreferringReaderWriterLock &) = delete;

    void AcquireReaderLock()
    {
        readTryMutex_.Acquire();

        std::unique_lock<std::mutex> readCountLock(readCountMutex_);
        readCount_++;
        if (readCount_ == 1)
            resourceMutex_.Acquire();

        readTryMutex_.Release();
    }

    void ReleaseReaderLock()
    {
        std::unique_lock<std::mutex> readCountLock(readCountMutex_);
        readCount_--;
        if (readCount_ == 0)
            resourceMutex_.Release();
    }

    void AcquireWriterLock()
    {
        std::unique_lock<std::mutex> writeCountLock(writeCountMutex_);
        writeCount_++;
        if (writeCount_ == 1)
            readTryMutex_.Acquire();

        resourceMutex_.Acquire();
    }

    void ReleaseWriterLock()
    {
        resourceMutex_.Release();

        std::unique_lock<std::mutex> writeCountLock(writeCountMutex_);
        writeCount_--;
        if (writeCount_ == 0)
            readTryMutex_.Release();
    }

private:
    int readCount_ = 0;
    int writeCount_ = 0;
    Semaphore resourceMutex_;
    std::mutex readCountMutex_;
    std::mutex writeCountMutex_;
    Semaphore readTryMutex_;
};


#endif // READER_WRITER_LOCK_HPP_


// References:
// Multithreading applications in Win32, Chapter 7
// https://en.wikipedia.org/wiki/Readers%E2%80%93writers_problem
// https://en.wikipedia.org/wiki/Readers%E2%80%93writer_lock
// Modern Operating System, 2.5.2 The Readers and Writers Problem
