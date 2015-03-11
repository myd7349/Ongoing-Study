#include "stdafx.h"
#include "RemoteMediaUtility.h"

#include <tlhelp32.h>
#include <psapi.h>
#include <rpc.h>

#include <cstdlib>
#include <ctime>

#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "rpcrt4.lib")

#include <cstdlib>

ULONGLONG cmGetFileSize(LPCTSTR lpcszFileName)
{
    WIN32_FIND_DATA fd;
    HANDLE hFile = ::FindFirstFile(lpcszFileName, &fd);
    if (INVALID_HANDLE_VALUE == hFile)
    {
        return 0;
    }
    else
    {
        ::FindClose(hFile);
        return (((ULONGLONG)fd.nFileSizeHigh << 32) | (ULONGLONG)fd.nFileSizeLow);
    }
}

CString &cmGetReadableFileSize(CString &strSize, const ULONGLONG &ullSizeInBytes)
{
#if 0
    if (ullSizeInBytes < 1024) // smaller than 1 KB
    {
        strSize.Format(_T("%I64u B"), ullSizeInBytes);
    }
    else if (ullSizeInBytes < 1024 * 1024) // smaller than 1 M
    {
        strSize.Format(_T("%.2lf KB"), 
            ullSizeInBytes / 1024.0);
    }
    else if (ullSizeInBytes < 1024 * 1024 * 1024) // smaller than 1 G
    {
        strSize.Format(_T("%.2lf MB"), 
            ullSizeInBytes / (1024.0 * 1024.0));
    }
    else if (ullSizeInBytes < 1024.0 * 1024 * 1024 * 1024) // smaller than 1 T
    {
        strSize.Format(_T("%.2lf GB"), 
            ullSizeInBytes / (1024.0 * 1024.0 * 1024.0));
    }
    else
    {
        strSize.Format(_T("%.2lf TB"), 
            ullSizeInBytes / (1024.0 * 1024.0 * 1024.0 * 1024.0));
    }
#else
    if (ullSizeInBytes < 1024 * 1024 * 1024) // smaller than 1 G
    {
        if (ullSizeInBytes >= 1024 * 1024) // bigger than 1M
        {
            strSize.Format(_T("%.2lf MB"), 
                ullSizeInBytes / (1024.0 * 1024.0));
        }
        else // smaller than 1M
        {
            if (ullSizeInBytes < 1024) // smaller than 1 KB
            {
                strSize.Format(_T("%I64u B"), ullSizeInBytes);
            }
            else // KB
            {
                strSize.Format(_T("%.2lf KB"), 
                    ullSizeInBytes / 1024.0);
            }
        }
    }
    else // bigger than 1G
    {
        if (ullSizeInBytes < 1024.0 * 1024 * 1024 * 1024) // smaller than 1 T
        {
            strSize.Format(_T("%.2lf GB"), 
                ullSizeInBytes / (1024.0 * 1024.0 * 1024.0));
        }
        else
        {
            strSize.Format(_T("%.2lf TB"), 
                ullSizeInBytes / (1024.0 * 1024.0 * 1024.0 * 1024.0));
        }
    }
#endif
    return strSize;
}

class _cmCFileSizeCmpHelper
{
public:
    enum FILESIZE_UNIT
    {
        B, 
        KB, 
        MB, 
        GB,
        TB
    };
    _cmCFileSizeCmpHelper()
    {
        m_mapFileSizeUnit[_T(" B")] = B; // Caution
        m_mapFileSizeUnit[_T("KB")] = KB;
        m_mapFileSizeUnit[_T("MB")] = MB;
        m_mapFileSizeUnit[_T("GB")] = GB;
        m_mapFileSizeUnit[_T("TB")] = TB;
    }
    ~_cmCFileSizeCmpHelper() {}
public:
    FILESIZE_UNIT GetUnit(const CString &strUnit)
    {
        FILESIZE_UNIT unit;
        if (m_mapFileSizeUnit.Lookup(strUnit, unit))
        {
            return unit;
        }
        throw FALSE;
    }
private:
    _cmCFileSizeCmpHelper(const _cmCFileSizeCmpHelper &);
    _cmCFileSizeCmpHelper &operator=(const _cmCFileSizeCmpHelper &);
private:
    CMap<CString, LPCTSTR, FILESIZE_UNIT, const FILESIZE_UNIT &> m_mapFileSizeUnit;
};

// 这个函数必须与cmGetReadableFileSize相对应。
int cmCompareReadableFileSize(const CString &strLSize, const CString &strRSize)
{
    static _cmCFileSizeCmpHelper s_fileSizeHelper;

    CString strLUnit = strLSize.Right(2);
    CString strRUnit = strRSize.Right(2);

    if (strLUnit != strRUnit)
    {
        _cmCFileSizeCmpHelper::FILESIZE_UNIT unitL, unitR;
        try
        {
            unitL = s_fileSizeHelper.GetUnit(strLUnit);
            unitR = s_fileSizeHelper.GetUnit(strRUnit);
            return unitL - unitR;
        }
        catch (...)
        {
        }
    }

    return (int)(_tcstod(strLSize, NULL) 
        - _tcstod(strRSize, NULL));
}

CString &cmGetModulePathName(CString &strPath, HMODULE hMod)
{
    TCHAR szModPath[_MAX_PATH];
    DWORD dwLastErr = ::GetLastError();

    ::SetLastError(ERROR_SUCCESS);
    ::GetModuleFileName(hMod, szModPath, _countof(szModPath));
    if (::GetLastError() == ERROR_SUCCESS)
    {
        strPath = szModPath;
        int iSlash = strPath.ReverseFind(_T('\\'));
        if (iSlash != -1)
        {
            strPath = strPath.Left(iSlash + 1);
        }
        else
        {
            strPath = strPath.Left(strPath.ReverseFind(_T('/')) + 1);
        }
    }
    else
    {
        strPath.Empty();
    }
    
    ::SetLastError(dwLastErr);
    return strPath;
}

CString &cmGetFullPath(CString &strFullPath, const CString &strPath, const CString &strFile)
{
    strFullPath = strPath;
    int iLen = strPath.GetLength();
    if (iLen > 0 && strPath[iLen - 1] != _T('\\')
        && strPath[iLen - 1] != _T('/'))
    {
        strFullPath += _T('\\');
    }
    strFullPath += strFile;
    return strFullPath;
}

BOOL cmIsExeRunning(LPCTSTR lpcszExeFile)
{
    HANDLE hProcSnap;

    hProcSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hProcSnap)
    {
        return FALSE;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(pe32);
    if (!::Process32First(hProcSnap, &pe32))
    {
        return FALSE;
    }


    do 
    {
        // TODO
        // 这里，也可以先调用OpenProcess获取进程句柄，然后
        // 使用如下函数获取进程对应的可执行文件的名字。
        // EnumProcesses + GetModuleBaseName
        // QueryFullProcessImageName
        // GetProcessImageFileName // See MSDN
        // GetModuleFileNameEx
        // 但是我在使用后两个函数的时候总遇到错误5（Access denied）
        if (::lstrcmpi(lpcszExeFile, pe32.szExeFile) == 0)
        {
            ::CloseHandle(hProcSnap);
            return TRUE;
        }
    } while (::Process32Next(hProcSnap, &pe32));
    ::CloseHandle(hProcSnap);
    return FALSE;
}

CString &cmTimeSecs2HMS(CString &strTime, const DWORD &dwTimeInSecs)
{
    // 以下代码段是错误的
    // CTime timeFmt((__time64_t)dwTimeInSecs);
    // strTime.Format(_T("%02d:%02d:%02d"), 
    //    timeFmt.GetHour(), timeFmt.GetMinute(), timeFmt.GetSecond());

    DWORD dwHour = dwTimeInSecs / 3600;
    DWORD dwMin  = dwTimeInSecs % 3600 / 60;
    DWORD dwSec  = dwTimeInSecs % 60;
    strTime.Format(_T("%02d:%02d:%02d"), dwHour, dwMin, dwSec);
    return strTime;
}

CString &cmGetCurDateTime(CString &strDateTime)
{
    std::time_t  timer = std::time(NULL);
#if 0
    std::tm     *today = std::localtime(&timer);

    TCHAR        szDateTime[32];

    _tcsftime(szDateTime, _countof(szDateTime), 
        _T("%Y-%m-%d %H:%M:%S"), today);
    strDateTime = szDateTime;
#else
    std::tm today;
    localtime_s(&today, &timer);
    TCHAR   szDateTime[32];

    _tcsftime(szDateTime, _countof(szDateTime), 
        _T("%Y-%m-%d %H:%M:%S"), &today);
    strDateTime = szDateTime;
#endif
    return strDateTime;
}

BOOL cmGetErrMsg(CString &strMsgContainer, 
    const DWORD &dwErrCode, const WORD &wLangID)
{
    strMsgContainer.Empty();

    LPVOID lpvErrMsgBuf = NULL;

    if (::FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER 
        | FORMAT_MESSAGE_FROM_SYSTEM 
        | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, dwErrCode, wLangID,
        (LPTSTR)&lpvErrMsgBuf, 0, NULL) != 0)
    {
        strMsgContainer = (LPTSTR)lpvErrMsgBuf;
        ::LocalFree(lpvErrMsgBuf);
        return TRUE;
    }
    else
    {
        ASSERT(NULL == lpvErrMsgBuf);
#if 0
        strMsgContainer.Format(
            _T("*** Error message from ErrorLookupEx:\r\n")
            _T("Invoke FormatMessage failed in %s(%d)."), 
            _T(__FUNCTION__), ::GetLastError());
#endif
        return FALSE;
    }
}

CString &cmGenerateGUID(CString &strGUID)
{
    GUID guid;

    if (::UuidCreate(&guid) != RPC_S_OK)
    {
        strGUID.Empty();
    }
    else
    {
        strGUID.Format(_T("{%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}"), 
            guid.Data1, guid.Data2, guid.Data3,
            guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
            guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
    }

    return strGUID;
}

// -- cmCIcon class begin
cmCIcon::cmCIcon() throw()
    : m_hICO(NULL)
{
}

cmCIcon::~cmCIcon()
{
    Free();
}

BOOL cmCIcon::Load(UINT uResID, HINSTANCE hResInst)
{
    Free();

    m_hICO = (HICON)::LoadImage(hResInst, MAKEINTRESOURCE(uResID), 
        IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
    return m_hICO != NULL;
}

void cmCIcon::Free()
{
    if (m_hICO != NULL)
    {
        ::DestroyIcon(m_hICO);
        m_hICO = NULL;
    }
}

// -- cmCIcon class end

// -- cmCBytes class begin
cmCBytes::cmCBytes(const DWORD &dwSize) 
    : m_lpbyBuf(NULL)
    , m_dwSizeInBytes(0)
{
    if (dwSize <= sizeof(m_byArr))
    {
        m_lpbyBuf = m_byArr;
        m_dwSizeInBytes = sizeof(m_byArr);
    }
    else
    {
        try
        {
            m_lpbyBuf = new BYTE[dwSize];
            m_dwSizeInBytes = dwSize;
        }
        catch (...)
        {
            m_lpbyBuf = NULL;
        }
    }
}

cmCBytes::~cmCBytes()
{
    if (m_lpbyBuf != NULL && m_lpbyBuf != m_byArr)
    {
        delete []m_lpbyBuf;
    }
}
// -- cmCBytes class end

