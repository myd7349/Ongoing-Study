#include "stdafx.h"

#include "Utility.h"

#include <algorithm>

#include <propvarutil.h>
#include <shlwapi.h>
#include <strsafe.h>
#pragma comment(lib, "propsys.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "strsafe.lib")

CString GetModulePath(HMODULE hModule)
{
    CString strDir;

    LPTSTR lpszBuf = strDir.GetBuffer(MAX_PATH);
    ::SetLastError(ERROR_SUCCESS);
    ::GetModuleFileName(hModule, lpszBuf, strDir.GetAllocLength());
    DWORD dwLastErr = ::GetLastError();
    strDir.ReleaseBuffer();

    if (dwLastErr != ERROR_SUCCESS)
    {
        return _T("");
    }

    TransformPathSep(strDir);

    int iLastPathSepPos = strDir.ReverseFind(_T('\\'));
    if (iLastPathSepPos != -1)
    {
        return strDir.Left(iLastPathSepPos + 1);
    }
    else
    {
        return _T("");
    }
}

// Note that:
// 1. JoinPath(_T("E:\\data\\data.dat"), _T("E:\\data\\data.dat")) will return
// _T("E:\\data\\data.dat").
// 2. JoinPath(_T("E:\\data"), _T("E:\\data\\data.dat")) will return
// _T("E:\\data\\data.dat").
CString JoinPath(LPCTSTR lpszBaseDir, LPCTSTR lpszSubDir)
{
    TCHAR szPath[MAX_PATH];
    LPTSTR lpszFullPath = ::PathCombine(szPath,
        lpszBaseDir != NULL ? lpszBaseDir : _T(""),
        lpszSubDir != NULL ? lpszSubDir : _T(""));

    TransformPathSep(lpszFullPath);

    if (lpszFullPath != NULL)
    {
        TCHAR szNormPath[MAX_PATH];

        // Canonicalize given path:
        // D:\Project\Debug\..\data -> D:\Project\data
        // 
        // Note that:
        // D:\Project\Debug\../data -> D:\Project\Debug\../data
        if (::PathCanonicalize(szNormPath, szPath))
        {
            return szNormPath;
        }
        else
        {
            return _T("");
        }
    }
    else
    {
        return _T("");
    }
}

LPTSTR TransformPathSep(LPTSTR lpszPath)
{
    if (NULL == lpszPath)
    {
        return lpszPath;
    }

    size_t len = 0;
    if (SUCCEEDED(::StringCchLength(lpszPath, MAX_PATH, &len)))
    {
        std::replace(lpszPath, lpszPath + len, _T('/'), _T('\\'));
    }
    return lpszPath;
}

CString TransformPathSep(const CString &strPath)
{
    CString strPathCopy = strPath;
    LPTSTR lpszBuf = strPathCopy.GetBuffer();
    TransformPathSep(lpszBuf);
    strPathCopy.ReleaseBuffer();

    return strPathCopy;
}

// 2015-05-07T09:33+08:00
BOOL HasLastPathSep(const CString &strPath)
{
    int iLen = strPath.GetLength();

    return iLen > 0 && (strPath[iLen - 1] == _T('\\') 
        || strPath[iLen - 1] == _T('/')); 
}

// 2015-05-07T09:33+08:00
CString AddLastPathSep(const CString &strPath)
{
    if (!HasLastPathSep(strPath))
    {
        return strPath + _T('\\');
    }
    else
    {
        return strPath;
    }
}

// 2015-05-07T09:33+08:00
CString RemoveLastPathSep(const CString &strPath)
{
    if (HasLastPathSep(strPath))
    {
        return strPath.Left(strPath.GetLength() - 1);
    }
    else
    {
        return strPath;
    }
}

BOOL IsRemovableDrive(LPCTSTR lpcszDrive)
{
    return ::GetDriveType(lpcszDrive) == DRIVE_REMOVABLE;
}

#if 0
// 2015-03-10T13:39+08:00
// MakeFullPath do similar work as boost::filesystem::create_directories.
// In cmd, we can use the internal command `md`/`mkdir` to create a directory.
// http://code.reactos.org/browse/reactos/trunk/reactos/base/shell/cmd/internal.c?hb=true
// 2015-04-23T09:21+08:00
// Deprecated, use SHCreateDirectory(Ex) instead.
BOOL MakeFullPath(const CString &strPath)
{
    TCHAR szNormPath[MAX_PATH];
    if (!PathCanonicalize(szNormPath, strPath.GetString()))
    {
        return FALSE;
    }

    if (CreateDirectory(szNormPath, NULL))
    {
        return TRUE;
    }
    else if (GetLastError() != ERROR_PATH_NOT_FOUND)
    {
        return FALSE;
    }

    LPCTSTR p = szNormPath;

    /* got ERROR_PATH_NOT_FOUND, so try building it up one component at a time */
    if (p[0] && p[1] == _T(':'))
    {
        p += 2;
    }

    while (*p == _T('\\'))
    {
        p++; /* skip drive root */
    }

    TCHAR szPath[MAX_PATH];
    INT_PTR n;

    do
    {
        p = _tcschr(p, _T('\\'));
        n = p ? p++ - szNormPath : _tcslen(szNormPath);
        _tcsncpy(szPath, szNormPath, n);
        szPath[n] = _T('\0');

        if (!CreateDirectory(szPath, NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
        {
            return FALSE;
        }
    } while (p != NULL);

    return TRUE;
}
#endif

// 2015-04-09T09:56+08:00
CString GetDirName(const CString &strPath)
{
    int iLastPathSepPos = strPath.ReverseFind(_T('\\'));
    if (-1 == iLastPathSepPos) 
    {
        iLastPathSepPos = strPath.ReverseFind(_T('/'));
        if (-1 == iLastPathSepPos)
        {
            return strPath;
        }
    }

    return strPath.Left(iLastPathSepPos + 1);
}

// 2015-04-23T13:45+08:00
CString BrowseForFolder(const CString &strTitle, HWND hParent, BOOL bShowFile, const CString &strRoot)
{
    TCHAR szFolder[MAX_PATH] = _T("");
    
    BROWSEINFO bi = {};
    bi.hwndOwner = hParent;
    bi.pszDisplayName = szFolder;
    bi.lpszTitle = strTitle;
    bi.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS;

    if (bShowFile)
    {
        bi.ulFlags |= BIF_BROWSEINCLUDEFILES;
    }

    PIDLIST_ABSOLUTE pidl = SHBrowseForFolder(&bi);
    if (pidl != NULL && SHGetPathFromIDList(pidl, szFolder))
    {
        return szFolder;
    }

    return _T("");
}

// 2015-03-11T17:06+08:00
// Windows also provides us an API:
// DWORD WINAPI GetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh);
// Please note the difference between them.
ULONGLONG GetFileSize(LPCTSTR lpcszFileName)
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

CString GetReadableFileSize(ULONGLONG ullSizeInBytes)
{
    CString strSize;

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

    return strSize;
}

class _CFileSizeCmpHelper
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
    _CFileSizeCmpHelper()
    {
        m_mapFileSizeUnit[_T(" B")] = B; // Caution
        m_mapFileSizeUnit[_T("KB")] = KB;
        m_mapFileSizeUnit[_T("MB")] = MB;
        m_mapFileSizeUnit[_T("GB")] = GB;
        m_mapFileSizeUnit[_T("TB")] = TB;
    }
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
    _CFileSizeCmpHelper(const _CFileSizeCmpHelper &);
    _CFileSizeCmpHelper &operator=(const _CFileSizeCmpHelper &);
private:
    CMap<CString, LPCTSTR, FILESIZE_UNIT, const FILESIZE_UNIT &> m_mapFileSizeUnit;
};

// 这个函数必须与GetReadableFileSize相对应。
int CompareReadableFileSize(const CString &strLSize, const CString &strRSize)
{
    static _CFileSizeCmpHelper s_fileSizeHelper;
    CString strLUnit = strLSize.Right(2);
    CString strRUnit = strRSize.Right(2);
    if (strLUnit != strRUnit)
    {
        _CFileSizeCmpHelper::FILESIZE_UNIT unitL, unitR;
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
    return Compare(_tcstod(strLSize, NULL), _tcstod(strRSize, NULL));
}

// 2015-08-27T10:01+08:00
#define VT_TO_STR(fmt, mem) \
    do \
    { \
        CString strValue; \
        strValue.Format(fmt, mem((&varIn))); \
        return strValue; \
    } while (0)

#if 0
// It seems that VariantToString:
// 1. can convert int/unsigned/double to string properly;
// 2. can not convert float properly;
CString VariantToCString(REFVARIANT varIn)
{
    switch (varIn.vt)
    {
    case VT_BSTR: return varIn.bstrVal;
    case VT_R4: VT_TO_STR(_T("%f"), V_R4);
    default: break;
    }

    if (varIn.vt == VT_BSTR)
        return varIn.bstrVal;

    WCHAR szBuffer[1024];
    if (SUCCEEDED(VariantToString(varIn, szBuffer, ARRAYSIZE(szBuffer))))
        return CW2T(szBuffer);
    else
        return _T("");
}
#else
CString VariantToCString(REFVARIANT varIn)
{
    switch (varIn.vt)
    {
    case VT_NULL: break;
    case VT_ERROR: break;
    case VT_EMPTY: break;
    case VT_BSTR: return LPCTSTR(V_BSTR(&varIn));
    case VT_BOOL: VT_TO_STR(_T("%d"), V_BOOL);
    case VT_INT: VT_TO_STR(_T("%d"), V_INT);
    case VT_I1: VT_TO_STR(_T("%d"), V_I1);
    case VT_I2: VT_TO_STR(_T("%d"), V_I2);
    case VT_I4: VT_TO_STR(_T("%ld"), V_I4);
    case VT_I8: VT_TO_STR(_T("%I64d"), V_I8);
    case VT_UINT: VT_TO_STR(_T("%u"), V_UINT);
    case VT_UI1: VT_TO_STR(_T("%d"), V_UI1);
    case VT_UI2: VT_TO_STR(_T("%hu"), V_UI2);
    case VT_UI4: VT_TO_STR(_T("%u"), V_UI4);
    case VT_UI8: VT_TO_STR(_T("%I64u"), V_UI8);
    case VT_R4: VT_TO_STR(_T("%f"), V_R4);
    case VT_R8: VT_TO_STR(_T("%lf"), V_R8);
    default: break;
    }

    return _T("");
}
// http://www.codeproject.com/Articles/542/CString-Management
#endif

// 2015-09-10T12:27+08:00
CString ExceptionToString(CException *e, LPCTSTR lpcszPrefix)
{
    ATLASSERT(e != NULL && e->IsKindOf(RUNTIME_CLASS(CException)));
    ATLASSERT(lpcszPrefix != NULL);

    CString strError;
    TCHAR szError[1024] = _T("");
    if (e->GetErrorMessage(szError, ARRAYSIZE(szError))) {
        if (lpcszPrefix == NULL || lpcszPrefix[0] == _T('\0'))
            strError = szError;
        else
            strError.Format(_T("%s:\n%s"), lpcszPrefix, szError);
    }

    return strError;
}

// 2015-09-10T12:27+08:00
void TraceException(CException *e, LPCTSTR lpcszPrefix)
{
    CString strError = ExceptionToString(e, lpcszPrefix);
    if (!strError.IsEmpty())
        ATLTRACE(_T("%s\n"), strError.GetString());
}

// 2016-01-20T10:42+08:00
CString GetSerialPort(LPCTSTR lpcszName)
{
    ASSERT(lpcszName != NULL);

    CRegKey hKey;
    if (hKey.Open(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DEVICEMAP\\SERIALCOMM"), KEY_READ) != ERROR_SUCCESS)
    {
        return _T("");
    }

    TCHAR szValue[16];
    ULONG ulChars = ARRAYSIZE(szValue);
    if (hKey.QueryStringValue(lpcszName, szValue, &ulChars) != ERROR_SUCCESS)
    {
        return _T("");
    }

    return szValue;
}

int GetSerialPortNumber(LPCTSTR lpcszName)
{
    CString strPort = GetSerialPort(lpcszName);
    if (strPort.IsEmpty())
    {
        return -1;
    }

    if (strPort.Left(3).MakeUpper() == _T("COM"))
    {
        return _ttoi(strPort.Mid(3));
    }

    return -1;
}

DWORD Execute(LPCTSTR lpcszCmdline, WORD wShowWindow, BOOL bSync)
{
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    si.lpTitle = TEXT("");
    si.dwFlags = STARTF_USESHOWWINDOW;   
    si.wShowWindow = wShowWindow;

    PROCESS_INFORMATION pi = { NULL };
    TCHAR szCmdLine[1024];

    lstrcpyn(szCmdLine, lpcszCmdline, _countof(szCmdLine));

    if (CreateProcess(NULL, szCmdLine, NULL, NULL, 
        FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
    {
        CloseHandle(pi.hThread);

        if (bSync)
        {
            WaitForSingleObject(pi.hProcess, INFINITE);
            DWORD dwExitCode;
            GetExitCodeProcess(pi.hProcess, &dwExitCode);

            CloseHandle(pi.hProcess);
            return dwExitCode;
        }
        else
        {
            CloseHandle(pi.hProcess);
            return 0;
        }
    }

    return 1;
}