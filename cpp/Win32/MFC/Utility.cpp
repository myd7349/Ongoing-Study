#include "stdafx.h"

#include "Utility.h"

#include <algorithm>

#include <shlwapi.h>
#include <strsafe.h>
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

CString &TransformPathSep(CString &strPath)
{
    LPTSTR lpszBuf = strPath.GetBuffer();
    TransformPathSep(lpszBuf);
    strPath.ReleaseBuffer();

    return strPath;
}

BOOL IsRemovableDrive(LPCTSTR lpcszDrive)
{
    return ::GetDriveType(lpcszDrive) == DRIVE_REMOVABLE;
}

// 2015-03-10T13:39+08:00
// MakeFullPath do similar work as boost::filesystem::create_directories.
// In cmd, we can use the internal command `md`/`mkdir` to create a directory.
// http://code.reactos.org/browse/reactos/trunk/reactos/base/shell/cmd/internal.c?hb=true
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

CString GetReadableFileSize(const ULONGLONG &ullSizeInBytes)
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
