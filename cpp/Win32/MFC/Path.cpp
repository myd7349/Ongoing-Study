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

