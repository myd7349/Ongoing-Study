// 2014-05-20T09:44+08:00
#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <psapi.h>
#pragma comment(lib, "strsafe.lib")
#pragma comment(lib, "psapi.lib")

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

#ifdef _UNICODE
#  define tcout std::wcout
#  define tstring std::wstring
#else
#  define tcout std::cout
#  define tstring std::string
#endif

template <typename T>
class Buffer
{
public:
    Buffer(DWORD dwBufferLen = 0)
    {
        _bufferLen = 0;
        _pBuffer = NULL;

        if (dwBufferLen != 0)
        {
            _Alloc(dwBufferLen);
        }
    }
    virtual ~Buffer()
    {
        _Free();
    }
    DWORD GetLength() const
    {
        return _bufferLen;
    }
    BOOL Resize(DWORD dwBufferLen)
    {
        return _Alloc(dwBufferLen);
    }
    /* explicit */operator T *()
    {
        return _pBuffer;
    }
    T &operator [](DWORD ind)
    {
        if (ind >= GetLength())
        {
            throw std::out_of_range("Index out of range.");
        }
        return _pBuffer[ind];
    }
    const T &operator [](DWORD ind) const
    {
        if (ind >= GetLength())
        {
            throw std::out_of_range("Index out of range.");
        }
        return _pBuffer[ind];
    }
protected:
    BOOL _Alloc(DWORD dwLen)
    {
        if (dwLen == _bufferLen)
        {
            return TRUE;
        }

        _Free();

        _pBuffer = reinterpret_cast<T *>(::HeapAlloc(
            ::GetProcessHeap(), HEAP_ZERO_MEMORY, dwLen * sizeof(T)));
        if (_pBuffer != NULL)
        {
            _bufferLen = dwLen;
            return TRUE;
        }
        else
        {
            _bufferLen = 0;
            throw std::runtime_error("::HeapAlloc failed.");
        }
    }
    void _Free()
    {
        if (_pBuffer != NULL)
        {
            if (::HeapFree(::GetProcessHeap(), HEAP_NO_SERIALIZE, _pBuffer))
            {
                _pBuffer = NULL;
                _bufferLen = 0;
            }
            else
            {
                throw std::runtime_error("::HeapFree failed.");
            }
        }
    }
private:
    Buffer(const Buffer &);
    Buffer &operator=(const Buffer &);
private:
    T *_pBuffer;
    DWORD _bufferLen;
};

template <typename _InIt>
void printV(_InIt first, _InIt last)
{
    while (first != last)
    {
        tcout << *first << _T(' ');
        ++first;
    }

    tcout << std::endl;
}

DWORD GetAllDrives(std::vector<TCHAR> &drives)
{
    drives.clear();

    DWORD dwDrivesCount = 0;

    DWORD dwMask = ::GetLogicalDrives();

    if (0 == dwMask)
    {
        return 0;
    }

    for (DWORD i=0; i<26; ++i)
    {
        if (dwMask & 1)
        {
            drives.push_back(static_cast<TCHAR>(_T('A') + i));
            ++dwDrivesCount;
        }
        dwMask >>= 1;
    }

    return dwDrivesCount;
}

#define _RETURN_DOS_DEVICE_NAME (0)

DWORD GetAllDrivesV2(std::vector<tstring> &drives)
{
    drives.clear();

    DWORD dwDrivesCount = 0;
    Buffer<TCHAR> buffer(128);

    DWORD dwRet = ::GetLogicalDriveStrings(buffer.GetLength() - 1, buffer);
    if (0 == dwRet)
    {
        return 0;
    }
    else if (dwRet > buffer.GetLength())
    {
        if (buffer.Resize(dwRet))
        {
            dwRet = ::GetLogicalDriveStrings(buffer.GetLength() - 1, buffer);
            if (0 == dwRet)
            {
                return FALSE;
            }
        }
        else
        {
            return FALSE;
        }
    }

    LPTSTR p = buffer;
    HRESULT hRet;
    std::size_t len;

#if _RETURN_DOS_DEVICE_NAME
    Buffer<TCHAR> dosDeviceName(128);
#endif
    while (SUCCEEDED(hRet = 
        ::StringCchLength(p, buffer.GetLength(), &len)) && len > 0)
    {
#if _RETURN_DOS_DEVICE_NAME
        TCHAR szDrive[3] = _T(" :");
        *szDrive = *p;
        if ((dwRet = ::QueryDosDevice(szDrive, dosDeviceName, 
            dosDeviceName.GetLength())) > 0)
        {
            drives.push_back(LPCTSTR(dosDeviceName));
        }
        else if (::GetLastError() == ERROR_INSUFFICIENT_BUFFER)
        {
            if (dosDeviceName.Resize(dwRet))
            {
                if (::QueryDosDevice(szDrive, dosDeviceName, 
                    dosDeviceName.GetLength()))
                {
                    drives.push_back(LPCTSTR(dosDeviceName));
                }
            }
        }
#else
        drives.push_back(p);
#endif
        p += len + 1; // while (*p++);
        ++dwDrivesCount;
    }

    return dwDrivesCount;
}

DWORD GetAllDrivers(std::vector<tstring> &drivers)
{
    drivers.clear();

    DWORD dwDriversCount = 0;

    Buffer<LPVOID> buffer(2048);

    DWORD dwCbNeeded = 0;
    if (::EnumDeviceDrivers(buffer, buffer.GetLength() * sizeof(LPVOID), &dwCbNeeded)
        && dwCbNeeded < buffer.GetLength() * sizeof(LPVOID))
    {
        DWORD dwCount = dwCbNeeded / sizeof(LPVOID);
        Buffer<TCHAR> DriveName(32);
        for (DWORD i = 0; i < dwCount; ++i)
        {
            if (::GetDeviceDriverBaseName(buffer[i], DriveName, DriveName.GetLength()))
            {
                drivers.push_back(LPCTSTR(DriveName));
                ++dwDriversCount;
            }
        }
    }

    return dwDriversCount;
}

BOOL IsUSBDrive(tstring DriveName)
{
    return ::GetDriveType(DriveName.c_str()) == DRIVE_REMOVABLE;
}

int _tmain()
{
    std::vector<TCHAR> vAllDrives;
    DWORD dwDrivesCount = GetAllDrives(vAllDrives);
    
    if (dwDrivesCount > 0)
    {
        tcout << _T("GetAllDrives: Totally ") << dwDrivesCount << _T(" drives found on this computer:\n");
        printV(vAllDrives.begin(), vAllDrives.end());
    }

    std::vector<tstring> vAllDriveStrings;
    dwDrivesCount = GetAllDrivesV2(vAllDriveStrings);
    
    if (dwDrivesCount > 0)
    {
        tcout << _T("GetAllDrivesV2: Totally ") << dwDrivesCount << _T(" drives found on this computer:\n");
        printV(vAllDriveStrings.begin(), vAllDriveStrings.end());
    }

#if 0
    dwDrivesCount = GetAllDrivers(vAllDriveStrings);
    
    if (dwDrivesCount > 0)
    {
        tcout << _T("GetAllDrivers: Totally ") << dwDrivesCount << _T(" drivers found on this computer:\n");
        printV(vAllDriveStrings.begin(), vAllDriveStrings.end());
    }
#endif

    std::vector<tstring> vUSBDrives;
    std::copy_if(vAllDriveStrings.begin(), vAllDriveStrings.end(), 
        std::back_inserter(vUSBDrives), IsUSBDrive);
    if (vUSBDrives.size() > 0)
    {
        tcout << _T("Totally ") << vUSBDrives.size() << _T(" Drives found on this computer:\n");
        printV(vUSBDrives.begin(), vUSBDrives.end());
    }

    _tsystem(_T("pause"));

    return 0;
}