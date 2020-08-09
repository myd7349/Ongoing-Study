// 2014-05-27T15:42+08:00
// By myd7349
#pragma once

#include <afxtempl.h>

#define RES_STR(id) CString(MAKEINTRESOURCE(id))

CString GetModuleFileName(HMODULE hModule = NULL);
CString GetModulePath(HMODULE hModule = NULL);
// TODO: A new version that accepts variant arguments.
CString JoinPath(LPCTSTR lpszBaseDir, LPCTSTR lpszSubDir);
CString JoinPath(LPCTSTR lpszBaseDir, LPCTSTR lpszSubDir, LPCTSTR lpcszFileName);
LPTSTR TransformPathSep(LPTSTR lpszPath);
CString TransformPathSep(const CString &strPath);

BOOL HasLastPathSep(const CString &strPath);
CString AddLastPathSep(const CString &strPath);
CString RemoveLastPathSep(const CString &strPath);

#if 0
__declspec(deprecated("Deprecated, use SHCreateDirectory(Ex) instead."))
BOOL MakeFullPath(const CString &strPath);
#else
#define MakeFullPath(path) (SHCreateDirectory(NULL, (path)) == ERROR_SUCCESS)
#endif

CString GetDirName(const CString &strPath);

__declspec(deprecated("Deprecated, use theApp.GetShellManager()->BrowseForFolder instead."))
CString BrowseForFolder(const CString &strTitle = _T(""),
    HWND hParent = NULL, BOOL bShowFile = FALSE, const CString &strRoot = _T(""));

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

ULONGLONG GetFileSize(LPCTSTR lpcszFileName);
CString GetReadableFileSize(ULONGLONG ullSizeInBytes);
int CompareReadableFileSize(const CString &strLSize, const CString &strRSize);

template <typename T>
int Compare(const T &lhs, const T &rhs)
{
    if (lhs < rhs)
        return -1;
    else if (rhs < lhs)
        return 1;

    return 0;
}

CString VariantToCString(REFVARIANT varIn);
inline CString VariantToCString(const _variant_t &varIn)
{
    return VariantToCString(static_cast<REFVARIANT>(varIn));
}
VARIANT CStringToVariant(const CString &strValue, VARTYPE vt);

CString ExceptionToString(CException *e, LPCTSTR lpcszPrefix = NULL);
void TraceException(CException *e, LPCTSTR lpcszPrefix = NULL);

CString GetSerialPort(LPCTSTR lpcszName = _T("\\Device\\Silabser0"));
int GetSerialPortNumber(LPCTSTR lpcszName = _T("\\Device\\Silabser0"));

DWORD Execute(LPCTSTR lpcszCmdline, WORD wShowWindow, BOOL bSync);

#define ExecDaemonSync(lpcszCmdline)  Execute((lpcszCmdline), SW_HIDE, TRUE)
#define ExecDaemonAsync(lpcszCmdline) Execute((lpcszCmdline), SW_HIDE, FALSE)
#define ExecAppSync(lpcszCmdline)     Execute((lpcszCmdline), SW_SHOW, TRUE)
#define ExecAppAsync(lpcszCmdline)    Execute((lpcszCmdline), SW_SHOW, FALSE)

int ListDirectory(
    CStringArray &arrstrItems, 
    const CString &strPattern, 
    const CString &strPath,
    BOOL bFullPath,
    BOOL bDirectory,
    BOOL bFile,
    int nLimit
    );
int FindFiles(CStringArray &arrstrFiles, 
    const CString &strFileNamePattern, 
    const CString &strPath, BOOL bFullPath, int nLimit = -1);
CString FindFirstFileWithName(const CString &strFileName, 
    const CString &strPath, BOOL bFullPath);

BOOL GetPEFixedFileVersion(const CString &strExeOrDllFilePath, VS_FIXEDFILEINFO &ffi);
CString GetPEFileVersion(const CString &strExeOrDllFilePath, BOOL bCompact = TRUE, BOOL bMoreCompact = FALSE);
CString GetPEProductVersion(const CString &strExeOrDllFilePath, BOOL bCompact = TRUE, BOOL bMoreCompact = FALSE);
CString GetFileInfoString(LPCTSTR lpcszExeOrDllFilePath, LPCTSTR lpcszStringName);
CString GetModuleFilePath(HMODULE hModule = NULL);

CString GetFullPath(LPCTSTR lpcszPath);

// boost::filesystem::remove_all
BOOL RemoveDirectoryEx(LPCTSTR lpcszDir, BOOL bToRecycleBin = FALSE);

// References:
// https://stackoverflow.com/questions/51949/how-to-get-file-extension-from-string-in-c
inline CString GetFileExt(CString strFileName)
{
    return PathFindExtension(strFileName);
}


CString GetFileName(LPCTSTR lpcszFilePath, BOOL bWithExt);


inline BOOL IsFileHasExt(LPCTSTR lpcszFilename, LPCTSTR lpcszExt)
{
    return _tcsicmp(PathFindExtension(lpcszFilename), lpcszExt) == 0;
}

BOOL BytesToImage(CImage &image, LPBYTE pBytes, DWORD dwSize);
