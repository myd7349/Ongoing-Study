// 2018-06-12T19:26+08:00
#ifndef READER_WRITER_LOCK_HPP_
#define READER_WRITER_LOCK_HPP_

#include <chrono>
#include <mutex>


class ReaderPreferringReaderWriterLock
{
public:
    ReaderPreferringReaderWriterLock() noexcept = default;

    ReaderPreferringReaderWriterLock(const ReaderPreferringReaderWriterLock &) = delete;
    ReaderPreferringReaderWriterLock &operator=(const ReaderPreferringReaderWriterLock &) = delete;

    void AcquireReaderLock()
    {
        std::unique_lock<std::mutex> lock(readersMutex);
        numberOfBlockingReaders_ += 1;
        if (numberOfBlockingReaders_ == 1)
            globalMutex.lock();
    }

    void ReleaseReaderLock()
    {
        std::unique_lock<std::mutex> lock(readersMutex);
        numberOfBlockingReaders_ -= 1;
        if (numberOfBlockingReaders_ == 0)
            globalMutex.unlock();
    }

    void AcquireWriterLock()
    {
        globalMutex.lock();
    }

    void ReleaseWriterLock()
    {
        globalMutex.unlock();
    }
    
    //void ReleaseLock();

    //bool AnyWritersSince(int sequence);
    //bool IsReaderLockHeld() const;
    //bool IsWriterLockHeld() const;
    //int GetWriterSequenceNumber() const;

private:
    int numberOfBlockingReaders_ = 0;
    std::mutex readersMutex;
    std::mutex globalMutex;
};


#endif // READER_WRITER_LOCK_HPP_


// References:
// Multithreading applications in Win32, Chapter 7
// https://en.wikipedia.org/wiki/Readers%E2%80%93writer_lock
