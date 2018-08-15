#include "CriticalSection.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>


class CriticalSectionImpl
{
public:
    CriticalSectionImpl()
    {
        InitializeCriticalSection(&cs_);
    }

    ~CriticalSectionImpl()
    {
        DeleteCriticalSection(&cs_);
    }

    void Lock()
    {
        EnterCriticalSection(&cs_);
    }

    bool TryLock()
    {
        return !!TryEnterCriticalSection(&cs_);
    }

    void Unlock()
    {
        LeaveCriticalSection(&cs_);
    }

private:
    CRITICAL_SECTION cs_;
};


CriticalSection::CriticalSection()
    : cs_(new CriticalSectionImpl())
{
}


CriticalSection::~CriticalSection()
{
}


void CriticalSection::Lock()
{
    cs_->Lock();
}


bool CriticalSection::TryLock()
{
    return cs_->TryLock();
}


void CriticalSection::Unlock()
{
    cs_->Unlock();
}


// References:
// Multithreading Applications in Win32, Ch09
// ...\Microsoft Visual Studio\2017\...\VC\Tools\MSVC\14.14.26428\crt\src\stl\primitives.h
// MFC:CCriticalSection
