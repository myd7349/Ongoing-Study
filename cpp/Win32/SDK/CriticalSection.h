#ifndef CRITICAL_SECTION_H_
#define CRITICAL_SECTION_H_


#ifdef CRITICAL_SECTION_HEADER_ONLY
# include "CriticalSection.cpp"

typedef CriticalSectionImpl CriticalSection;
#else
#include <memory>


class CriticalSectionImpl;


class CriticalSection
{
public:
    CriticalSection();
    virtual ~CriticalSection();

    void Lock();
    bool TryLock();
    void Unlock();

    void *GetHandle();

private:
    std::unique_ptr<CriticalSectionImpl> cs_;
};
#endif

#endif // CRITICAL_SECTION_H_
