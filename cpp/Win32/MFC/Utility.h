// 2014-05-27T15:42+08:00
#pragma once

#include <atlstr.h>
#include <afxtempl.h>

#define RES_STR(id) CString(MAKEINTRESOURCE(id))

CString GetModulePath(HMODULE hModule = NULL);
// TODO: A new version that accepts variant arguments.
CString JoinPath(LPCTSTR lpszBaseDir, LPCTSTR lpszSubDir);
LPTSTR TransformPathSep(LPTSTR lpszPath);
CString &TransformPathSep(CString &strPath);

BOOL IsRemovableDrive(LPCTSTR lpcszDrive);

template <typename _Pred>
DWORD GetDrives(CArray<CString> &arrDrives, _Pred p)
{
    arrDrives.RemoveAll();

    TCHAR szDrive[4] = _T(" :\\");
    DWORD dwDrivesMask = ::GetLogicalDrives();
    DWORD dwDrivesCount = 0;

    for (DWORD i=0; i<26; ++i)
    {
        if (dwDrivesMask & 1)
        {
            szDrive[0] = static_cast<TCHAR>(_T('A') + i);
            if (p(szDrive))
            {
                arrDrives.Add(szDrive);
                ++dwDrivesCount;
            }
        }
        dwDrivesMask >>= 1;
    }

    return dwDrivesCount;
}

