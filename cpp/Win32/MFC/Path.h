#pragma once

CString ReplaceFileExt(LPCTSTR lpcszFilePath, LPCTSTR lpcszNewExt);

CString GetFileTitle(LPCTSTR lpcszFilePath);

BOOL OpenFolderAndSelectItems(LPCTSTR lpcszFilePath);

BOOL OpenFolderAndSelectItems(LPCTSTR lpcszFileDir, LPCTSTR lpcszFileName, ...);

// TODO:
// https://github.com/CrashRpt/crashrpt2/blob/0c6ca1054fb7883f092a7c9bae1d5cd44467e33a/reporting/crashrpt/Utility.cpp#L304-L331
int DeleteFile(LPCTSTR lpcszPath, bool bPermanentDelete);

BOOL IsEquivalentPath(LPCTSTR lpcszPath1, LPCTSTR lpcszPath2);

// IsFile
// IsDirectory
// https://github.com/Blinue/Magpie/blob/e552e60621e6acbf9d87fec1770e797dcf74f546/Runtime/Utils.h#L58-L67
