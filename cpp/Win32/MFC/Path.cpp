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
