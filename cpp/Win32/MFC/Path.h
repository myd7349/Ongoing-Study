#pragma once

CString ReplaceFileExt(LPCTSTR lpcszFilePath, LPCTSTR lpcszNewExt);

CString GetFileTitle(LPCTSTR lpcszFilePath);

BOOL OpenFolderAndSelectItems(LPCTSTR lpcszFilePath);

BOOL OpenFolderAndSelectItems(LPCTSTR lpcszFileDir, LPCTSTR lpcszFileName, ...);
