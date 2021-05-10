// VLPLog.cpp : implementation file
//

#include "stdafx.h"
#include "VLPLog.h"

#include <cstdarg>
#include <clocale>

// CVLPLog
CStdioFile       CVLPLog::ms_hLogFile;
CCriticalSection CVLPLog::ms_cs;
CString          CVLPLog::ms_strContent;
SYSTEMTIME       CVLPLog::ms_SystemTime;
CString          CVLPLog::ms_strLongDateTime;


CVLPLog::CVLPLog()
{
}

CVLPLog::~CVLPLog()
{
}


// CVLPLog member functions
BOOL CVLPLog::Startup(LPCTSTR lpszLogFileName)
{
    if (_IsFileValid())
    {
        return TRUE;
    }

    CString strModuleName;
    CString strFullPath;

    ::GetModuleFileName(NULL, strModuleName.GetBufferSetLength(MAX_PATH), MAX_PATH);
    strFullPath = strModuleName;
    strModuleName.ReleaseBuffer();

    int nPathSepPos = strFullPath.ReverseFind(_T('\\'));
    ASSERT(nPathSepPos != -1);
    strFullPath.Truncate(nPathSepPos + 1);
    strFullPath += lpszLogFileName;

    _tsetlocale(LC_ALL, _T(""));

    CSingleLock singleLock(&ms_cs, TRUE);

    ms_hLogFile.Open(strFullPath, CStdioFile::modeCreate | CStdioFile::modeWrite);

    singleLock.Unlock();

    DumpToLog(_T("<<================ VLPLog Startup ===================>>\n"));

    return _IsFileValid();
}

void CVLPLog::DumpToLog(LPCTSTR lpszFmt, ...)
{
    ms_hLogFile.AssertValid();

    if (!_IsFileValid())
    {
        return;
    }

    CSingleLock singleLock(&ms_cs, TRUE);

    std::va_list pArgList;

    va_start(pArgList, lpszFmt);
    ms_strContent.FormatV(lpszFmt, pArgList);
    va_end(pArgList);

    if (ms_strContent.IsEmpty() || ms_strContent[ms_strContent.GetLength() - 1] != _T('\n'))
    {
        ms_strContent += _T('\n');
    }

    ::GetLocalTime(&ms_SystemTime);
    ms_strLongDateTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d.%03d> "), 
        ms_SystemTime.wYear, ms_SystemTime.wMonth, ms_SystemTime.wDay, 
        ms_SystemTime.wHour, ms_SystemTime.wMinute, ms_SystemTime.wSecond, ms_SystemTime.wMilliseconds);

    ms_hLogFile.WriteString(ms_strLongDateTime + ms_strContent);
    ms_hLogFile.Flush();
}

void CVLPLog::Shutdown()
{
    if (_IsFileValid())
    {
        DumpToLog(_T("<<================ VLPLog Shutdown ==================>>\n"));

        CSingleLock singleLock(&ms_cs, TRUE);

        ms_hLogFile.Close();
    }
}
