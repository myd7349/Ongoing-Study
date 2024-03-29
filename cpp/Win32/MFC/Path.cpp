#include "stdafx.h"
#include "Path.h"


CString ReplaceFileExt(LPCTSTR lpcszFilePath, LPCTSTR lpcszNewExt)
{
    ASSERT(lpcszFilePath != NULL);

    if (lpcszNewExt == NULL || lpcszNewExt[0] == _T('\0'))
        return lpcszFilePath;

    ASSERT(lpcszNewExt[0] == _T('.') && lpcszNewExt[1] != _T('\0'));

    TCHAR szDrive[_MAX_DRIVE] = _T("");
    TCHAR szDir[_MAX_DIR] = _T("");
    TCHAR szFilename[_MAX_FNAME] = _T("");
    TCHAR szExt[_MAX_EXT] = _T("");

    if (_tsplitpath_s(lpcszFilePath, szDrive, szDir, szFilename, szExt) == 0)
    {
        TCHAR szPath[_MAX_PATH] = _T("");
        if (_tmakepath_s(szPath, szDrive, szDir, szFilename, lpcszNewExt) == 0)
            return szPath;
    }
    
    return lpcszFilePath;
}



CString GetFileTitle(LPCTSTR lpcszFilePath)
{
    ASSERT(lpcszFilePath != NULL);

    TCHAR szFileTitle[MAX_PATH];
    if (::GetFileTitle(lpcszFilePath, szFileTitle, ARRAYSIZE(szFileTitle)) == 0)
        return szFileTitle;

    return _T("");
}


BOOL OpenFolderAndSelectItems(LPCTSTR lpcszFilePath)
{
    return OpenFolderAndSelectItems(lpcszFilePath, NULL);
}


BOOL OpenFolderAndSelectItems(LPCTSTR lpcszFileDir, LPCTSTR lpcszFileName, ...)
{
    ASSERT(lpcszFileDir != NULL);
    
    HRESULT hr;

    //hr = CoInitializeEx(0, COINIT_MULTITHREADED);
    //if (hr != S_OK)
    //    return FALSE;

    CString strFolder = GetDirName(lpcszFileDir);

    ATL::CPath filePath(lpcszFileDir);
    if (!filePath.FileExists())
    {
        ATL::CPath fileFolder(strFolder);
        if (!fileFolder.FileExists())
            return FALSE;
    }

    // SHSimpleIDListFromPath
    // SHGetDesktopFolder
    // https://stackoverflow.com/questions/47564192/shopenfolderandselectitems-with-arrays
    LPITEMIDLIST lpilFolder = ILCreateFromPath(strFolder);
    if (lpilFolder == nullptr)
    {
        //CoUninitialize();
        return FALSE;
    }

    std::vector<LPITEMIDLIST> vpil;
    if (!filePath.IsDirectory())
    {
        LPITEMIDLIST lpil = ILCreateFromPath(lpcszFileDir);
        if (lpil != nullptr)
            vpil.push_back(lpil);
    }

    if (lpcszFileName != NULL)
    {
        CString strTemp = JoinPath(strFolder, lpcszFileName);
        if (ATL::ATLPath::FileExists(strTemp) && !ATL::ATLPath::IsDirectory(strTemp))
        {
            LPITEMIDLIST lpil = ILCreateFromPath(strTemp);
            if (lpil != nullptr)
                vpil.push_back(lpil);
        }

        va_list args;

        va_start(args, lpcszFileName);

        while (true)
        {
            LPCTSTR lpcszFile = va_arg(args, LPCTSTR);
            if (lpcszFile == nullptr)
                break;

            strTemp = JoinPath(strFolder, lpcszFile);
            if (ATL::ATLPath::FileExists(strTemp) && !ATL::ATLPath::IsDirectory(strTemp))
            {
                LPITEMIDLIST lpil = ILCreateFromPath(strTemp);
                if (lpil != nullptr)
                    vpil.push_back(lpil);
            }
        }

        va_end(args);
    }

    hr = SHOpenFolderAndSelectItems(
        lpilFolder,
        static_cast<UINT>(vpil.size()),
        const_cast<LPCITEMIDLIST*>(vpil.data()),
        0
        );

    for (std::vector<LPITEMIDLIST>::size_type i = 0; i < vpil.size(); ++i)
        ILFree(vpil[i]);

    ILFree(lpilFolder);

    //CoUninitialize();

    return hr == S_OK;
}


int DeleteFile(LPCTSTR lpcszPath, bool bPermanentDelete)
{
    SHFILEOPSTRUCT fop = { 0 };

    TCHAR szFrom[MAX_PATH] = _T("");
    _tcscpy_s(szFrom, ARRAYSIZE(szFrom), lpcszPath);

    fop.fFlags |= FOF_SILENT | FOF_NOERRORUI | FOF_NOCONFIRMATION;
    if (bPermanentDelete)
        fop.fFlags &= ~FOF_ALLOWUNDO;
    else
        fop.fFlags |= FOF_ALLOWUNDO;

    fop.wFunc = FO_DELETE;
    fop.pFrom = szFrom;
    fop.pTo = nullptr;

    return SHFileOperation(&fop);
}


// https://stackoverflow.com/questions/562701/best-way-to-determine-if-two-path-reference-to-same-file-in-windows/562830#562830
BOOL IsEquivalentPath(LPCTSTR lpcszPath1, LPCTSTR lpcszPath2)
{
    ASSERT(lpcszPath1 != nullptr);
    ASSERT(lpcszPath2 != nullptr);

    HANDLE hFile1 = CreateFile(
        lpcszPath1,
        FILE_READ_ATTRIBUTES,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        nullptr,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS,
        nullptr);
    if (hFile1 == INVALID_HANDLE_VALUE)
        return FALSE;

    HANDLE hFile2 = CreateFile(
        lpcszPath2,
        FILE_READ_ATTRIBUTES,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        nullptr,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS,
        nullptr);
    if (hFile2 == INVALID_HANDLE_VALUE)
    {
        CloseHandle(hFile1);
        return FALSE;
    }

    BY_HANDLE_FILE_INFORMATION fileInformation1 = { 0 };
    if (!GetFileInformationByHandle(hFile1, &fileInformation1))
    {
        CloseHandle(hFile1);
        CloseHandle(hFile2);

        return FALSE;
    }
    
    // Note:
    // MSVC's std::filesystem::equivalent tries
    // GetFileInformationByHandleEx first, and
    // if it failed, uses GetFileInformationByHandle
    // as fallback.
    BY_HANDLE_FILE_INFORMATION fileInformation2 = { 0 };
    if (!GetFileInformationByHandle(hFile2, &fileInformation2))
    {
        CloseHandle(hFile1);
        CloseHandle(hFile2);

        return FALSE;
    }

    BOOL bEquivalent =
        fileInformation1.dwVolumeSerialNumber == fileInformation2.dwVolumeSerialNumber &&
        fileInformation1.nFileIndexHigh == fileInformation2.nFileIndexHigh &&
        fileInformation1.nFileIndexLow == fileInformation2.nFileIndexLow;

    CloseHandle(hFile1);
    CloseHandle(hFile2);

    return bEquivalent;
}


// References:
// TortoiseGit\src\Utils\PathUtils.h
// TortoiseGit\src\Utils\TempFile.h
// [Best way to determine if two path reference to same file in Windows?](https://stackoverflow.com/questions/562701/best-way-to-determine-if-two-path-reference-to-same-file-in-windows)
// https://github.com/MaskRay/ccls/blob/master/src/filesystem.cc
// [Generate temporary files with any extension](https://www.codeproject.com/Tips/314160/Generate-temporary-files-with-any-extension)
/*
BOOL GetTemporaryFilePath(CString strExtension, CString& strFileName)
{
     TCHAR lpszTempPath[MAX_PATH] = { 0 };
     if (!GetTempPath(MAX_PATH, lpszTempPath))
         return FALSE;

     TCHAR lpszFilePath[MAX_PATH] = { 0 };
     do {
         if (!GetTempFileName(lpszTempPath, NULL, 0, lpszFilePath))
             return FALSE;

         strFileName = lpszFilePath;
         VERIFY(::DeleteFile(strFileName));
         strFileName.Replace(_T(".tmp"), strExtension);
     }
     while (_taccess(strFileName, 00) != -1);

     OutputDebugString(_T("GetTemporaryFilePath = '") + strFileName + _T("'\n"));
     return TRUE;
}
*/
// https://github.com/libgit2/libgit2/blob/main/src/util/win32/path_w32.c
// https://github.com/ClassViewer/java-gui-launcher/blob/master/whereami/whereami.h
// https://github.com/bonsmile/lxd/blob/main/fileio.cpp
// https://github.com/sindresorhus/recycle-bin/blob/main/recycle-bin.c
// https://github.com/samhocevar/portable-file-dialogs/blob/main/portable-file-dialogs.h
