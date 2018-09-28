// 2018-08-15T21:03+08:00
#ifndef SRWLOCK_H_
#define SRWLOCK_H_

#ifdef SRWLOCK_HEADER_ONLY
# include "SRWLock.cpp"

typedef SRWLockImpl SRWLock;
#else

#include <memory>

class SRWLockImpl;


class SRWLock
{
public:
    SRWLock();
    virtual ~SRWLock();

    void Lock();
    bool TryLock();
    void Unlock();

    void LockShared();
    bool TryLockShared();
    void UnlockShared();

    void *GetHandle();

private:
    std::unique_ptr<SRWLockImpl> lock_;
};

#endif

#endif // SRWLOCK_H_
