#ifndef SINGLE_LOCK_H_
#define SINGLE_LOCK_H_

template <typename LockT>
class SingleLock
{
public:
    explicit SingleLock(LockT &lock)
        : lock_(lock)
    {
        lock_.Lock();
    }

    ~SingleLock()
    {
        lock_.Unlock();
    }

private:
    SingleLock(const SingleLock &) = delete;
    SingleLock &operator=(const SingleLock &) = delete;

    LockT &lock_;
};

#endif // SINGLE_LOCK_H_

// References:
// Multithreading Applications in Win32, Ch09
// MFC:CSingleLock
