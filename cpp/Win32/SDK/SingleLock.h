#ifndef SINGLE_LOCK_H_
#define SINGLE_LOCK_H_

#include <cassert>


template <typename LockT>
class SingleLock
{
public:
    explicit SingleLock(LockT &lock)
        : lock_(lock), owns_(false)
    {
        lock_.Lock();
        owns_ = true;
    }

    ~SingleLock()
    {
        if (owns_)
            lock_.Unlock();
    }

    void Lock()
    {
        lock_.Lock();
        owns_ = true;
    }

    void Unlock()
    {
        assert(owns_);

        lock_.Unlock();
        owns_ = false;
    }

    LockT &Mutex()
    {
        return lock_;
    }

    SingleLock(const SingleLock &) = delete;
    SingleLock &operator=(const SingleLock &) = delete;

private:
    LockT &lock_;
    bool owns_;
};

#endif // SINGLE_LOCK_H_

// References:
// Multithreading Applications in Win32, Ch09
// MFC:CSingleLock
// C++11: <mutex>
