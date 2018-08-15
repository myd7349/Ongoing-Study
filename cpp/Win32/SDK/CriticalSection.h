#ifndef CRITICAL_SECTION_H_
#define CRITICAL_SECTION_H_

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

private:
    std::unique_ptr<CriticalSectionImpl> cs_;
};

#endif // CRITICAL_SECTION_H_
