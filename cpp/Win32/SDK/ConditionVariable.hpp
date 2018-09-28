#pragma once

#include <exception>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "CriticalSection.h"
#include "SingleLock.h"
#include "SRWLock.h"


class ConditionVariable
{
public:
    enum WaitStatus
    {
        NoTimeout,
        Timeout,
        Error,
    };

    __forceinline ConditionVariable()
    {
        InitializeConditionVariable(&cv_);
    }

    __forceinline void NotifyOne()
    {
        WakeConditionVariable(&cv_);
    }

    __forceinline void NotifyAll()
    {
        WakeAllConditionVariable(&cv_);
    }

    template <typename MutexT>
    __forceinline void Wait(SingleLock<MutexT> &lock)
    {
        if (WaitFor(lock, INFINITE) == Error)
            std::terminate();
    }

    template <typename MutexT, typename PredicateT>
    __forceinline void Wait(SingleLock<MutexT> &lock, PredicateT pred)
    {
        while (!pred())
            Wait(lock);
    }

    template <typename MutexT>
    __forceinline WaitStatus WaitFor(SingleLock<MutexT> &lock, UINT timeout)
    {
        return WaitForImpl(lock, timeout);
    }

    template <typename MutexT, typename PredicateT>
    __forceinline bool WaitFor(SingleLock<MutexT> &lock, UINT timeout, PredicateT pred)
    {
        // TODO
        while (!pred())
        {
            if (WaitForImpl(lock, timeout) == Timeout)
                return pred();
        }

        return true;
    }

    template <typename MutexT>
    __forceinline WaitStatus WaitUntil(SingleLock<MutexT> &lock, UINT timePoint)
    {
        // TODO
    }

    template <typename MutexT, typename PredicateT>
    __forceinline bool WaitUntil(SingleLock<MutexT> &lock, UINT timePoint, PredicateT pred)
    {
        // TODO
    }

    __forceinline PCONDITION_VARIABLE GetHandle()
    {
        return &cv_;
    }

private:
    __forceinline WaitStatus WaitForImpl(SingleLock<CriticalSection> &lock, UINT timeout)
    {
        // TODO: Thread safety
        BOOL result = SleepConditionVariableCS(&cv_, reinterpret_cast<PCRITICAL_SECTION>(lock.Mutex().GetHandle()), timeout);
        if (result)
            return NoTimeout;

        if (GetLastError() == ERROR_TIMEOUT)
            return Timeout;
        else
            return Error;
    }

    __forceinline WaitStatus WaitForImpl(SingleLock<SRWLock> &lock, UINT timeout)
    {
        // TODO: Thread safety
        BOOL result = SleepConditionVariableSRW(&cv_, reinterpret_cast<PSRWLOCK>(lock.Mutex().GetHandle()), timeout, 0) != 0;
        if (result)
            return NoTimeout;

        if (GetLastError() == ERROR_TIMEOUT)
            return Timeout;
        else
            return Error;
    }

    CONDITION_VARIABLE cv_;
};

// References:
// https://docs.microsoft.com/en-us/windows/desktop/Sync/condition-variables
// cppreference:condition_variable
// https://stackoverflow.com/questions/3513045/conditional-variable-vs-semaphore
// ...\Microsoft Visual Studio\2017\...\VC\Tools\MSVC\14.14.26428\crt\src\stl\primitives.h
// Ongoing-Study/os/ProducerConsumerProblem/ProducerConsumerProblemCpp11v3/ProducerConsumerContextWin32.hpp
// https://currentmillis.com/
// https://gamedev.stackexchange.com/questions/26759/best-way-to-get-elapsed-time-in-miliseconds-in-windows
// https://stackoverflow.com/questions/3729169/how-can-i-get-the-windows-system-time-with-millisecond-resolution
// https://www.intel.com/content/dam/www/public/us/en/documents/white-papers/ia-32-ia-64-benchmark-code-execution-paper.pdf
// https://www.linuxquestions.org/questions/programming-9/how-to-convert-tsc-cpu-cycles-into-seconds-in-c-833190/
// https://docs.microsoft.com/en-us/windows/desktop/api/synchapi/nf-synchapi-sleepconditionvariablecs
// https://docs.microsoft.com/en-us/windows/desktop/api/synchapi/nf-synchapi-sleepconditionvariablesrw
// https://stackoverflow.com/questions/1218716/implementing-condition-variables-for-critical-sections-for-winthreads-for-xp
// https://stackoverflow.com/questions/11706985/win32-thread-safe-queue-implementation-using-native-windows-api
// https://docs.microsoft.com/zh-cn/windows/desktop/Sync/condition-variables
