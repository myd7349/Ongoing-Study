#include <cassert>
#include <iostream>
#include <shared_mutex>
#include <typeinfo>

#include "../../Stopwatch.h"
#include "../reader_writer_lock.hpp"


template <typename RWLockT>
class ThreadSafeCounter
{
public:
    ThreadSafeCounter() = default;

    int Get() const
    {
        lock_.AcquireReaderLock();
        int value = value_;
        lock_.ReleaseReaderLock();
        return value;
    }

    void Increment()
    {
        lock_.AcquireWriterLock();
        value_++;
        lock_.ReleaseWriterLock();
    }

    void Decrement()
    {
        lock_.AcquireWriterLock();
        value_--;
        lock_.ReleaseWriterLock();
    }

    void Reset()
    {
        lock_.AcquireWriterLock();
        value_ = 0;
        lock_.ReleaseWriterLock();
    }

private:
    mutable RWLockT lock_;
    int value_ = 0;
};


class SharedMutexAdapter
{
public:
    void AcquireReaderLock()
    {
        mutex_.lock_shared();
    }

    void ReleaseReaderLock()
    {
        mutex_.unlock_shared();
    }

    void AcquireWriterLock()
    {
        mutex_.lock();
    }

    void ReleaseWriterLock()
    {
        mutex_.unlock();
    }

private:
    mutable std::shared_mutex mutex_;
};


template <typename RWLockT>
int test()
{
    std::cout << "Using " << typeid(RWLockT).name() << std::endl;

    ThreadSafeCounter<RWLockT> counter;
    auto increment = [&counter]()
    {
        for (int i = 0; i < 10000000; ++i)
            counter.Increment();
    };

    auto decrement = [&counter]()
    {
        for (int i = 0; i < 5000000; ++i)
            counter.Decrement();
    };

    auto print = [&counter]()
    {
        std::cout << '[' << std::this_thread::get_id() << "] <" << counter.Get() << ">\n";
    };

    auto assert = [&counter]()
    {
        for (int i = 0; i < 30000000; ++i)
        {
            assert(counter.Get() <= 30000000);
        }
    };

    Stopwatch sw;

    sw.Start();

    std::thread thread1(decrement);
    std::thread thread2(increment);
    std::thread thread3(increment);
    std::thread thread4(print);
    std::thread thread5(increment);
    std::thread thread6(decrement);
    std::thread thread7(assert);

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    thread5.join();
    thread6.join();
    thread7.join();

    print();

    sw.Stop();
    std::cout << "Ellapsed milliseconds: " << sw.GetElapsedMilliseconds() << std::endl;

    return 0;
}


int main()
{
    test<ReaderPreferringReaderWriterLock>();
    test<WriterPreferringReaderWriterLock>();
    test<SharedMutexAdapter>();

    return 0;
}

// References:
// cppreference:shared_mutex
