#pragma once

#include <string>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


class SingleInstance
{
public:
    explicit SingleInstance(const std::wstring &guid,
        const std::wstring &title = L"", bool isGlobal = false)
        : hMutex_(NULL), dwLastError_(ERROR_SUCCESS)
        , guid_(guid), title_(title)
        , isGlobal_(isGlobal)
    {
        if (isGlobal)
            guid_ = L"Global\\" + guid_;

        hMutex_ = CreateMutexW(NULL, FALSE, guid_.c_str());
        dwLastError_ = GetLastError();

        if (IsAnotherInstanceRunning())
        {
            CloseHandle(hMutex_);
            hMutex_ = NULL;

            if (!title_.empty())
            {
                HWND hWnd = FindWindowW(NULL, title.c_str());
                if (hWnd != NULL)
                    SetForegroundWindow(hWnd);
            }
        }
    }

    ~SingleInstance()
    {
        if (hMutex_ != NULL)
            CloseHandle(hMutex_);
    }

    bool IsAnotherInstanceRunning() const
    {
        return dwLastError_ == ERROR_ALREADY_EXISTS;
    }

    bool IsPrimary() const
    {
        return !IsAnotherInstanceRunning();
    }

    bool IsSecondary() const
    {
        return IsAnotherInstanceRunning();
    }

private:
    SingleInstance(const SingleInstance &);
    SingleInstance &operator=(const SingleInstance &);

    HANDLE hMutex_;
    DWORD dwLastError_;
    std::wstring guid_;
    std::wstring title_;
    bool isGlobal_;
};


// References:
// https://www.codeproject.com/articles/538/avoiding-multiple-instances-of-an-application
// https://support.microsoft.com/en-us/help/243953/how-to-limit-32-bit-applications-to-one-instance-in-visual-c
// https://stackoverflow.com/questions/9660218/using-mutex-to-enforce-single-instance
// https://stackoverflow.com/questions/4191465/how-to-run-only-one-instance-of-application
// QtSingleApplication
