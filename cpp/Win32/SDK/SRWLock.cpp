#include "SRWLock.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>


class SRWLockImpl
{
public:
    SRWLockImpl()
    {
        InitializeSRWLock(&lock_);
    }

    ~SRWLockImpl()
    {
    }

    void Lock()
    {
        AcquireSRWLockExclusive(&lock_);
    }

    bool TryLock()
    {
        return !!TryAcquireSRWLockExclusive(&lock_);
    }

    void Unlock()
    {
        ReleaseSRWLockExclusive(&lock_);
    }

    void LockShared()
    {
        AcquireSRWLockShared(&lock_);
    }

    bool TryLockShared()
    {
        return !!TryAcquireSRWLockShared(&lock_);
    }

    void UnlockShared()
    {
        ReleaseSRWLockShared(&lock_);
    }

    SRWLOCK *GetHandle()
    {
        return &lock_;
    }

private:
    SRWLOCK lock_;
};


#ifndef SRWLOCK_HEADER_ONLY


SRWLock::SRWLock()
    : lock_(new SRWLockImpl())
{
}


SRWLock::~SRWLock()
{
}


void SRWLock::Lock()
{
    lock_->Lock();
}


bool SRWLock::TryLock()
{
    return lock_->TryLock();
}


void SRWLock::Unlock()
{
    lock_->Unlock();
}


void SRWLock::LockShared()
{
    lock_->LockShared();
}


bool SRWLock::TryLockShared()
{
    return lock_->TryLockShared();
}


void SRWLock::UnlockShared()
{
    lock_->UnlockShared();
}


void *SRWLock::GetHandle()
{
    return lock_->GetHandle();
}

#endif


// References:
// Multithreading Applications in Win32, Ch07
// ...\Microsoft Visual Studio\2017\...\VC\Tools\MSVC\14.14.26428\crt\src\stl\primitives.h
// https://github.com/anydream/SharedReadWriteLock
// https://github.com/cnr-isti-vclab/vcglib/blob/master/wrap/system/multithreading/rw_lock.h
// TortoiseGit\src\Utils\ReaderWriterLock.h
