// VLPLog.cpp : implementation file
//

#include "stdafx.h"
#include "VLPLog.h"

#include <cstdarg>
#include <clocale>

#ifdef _VLPLOG_ON

// CVLPLog
CStdioFile       CVLPLog::ms_hLogFile;
CCriticalSection CVLPLog::ms_cs;

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

    CSingleLock singleLock(&ms_cs);

    singleLock.Lock();
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
    CString strContent;
    std::va_list pArgList;

    va_start(pArgList, lpszFmt);
    strContent.FormatV(lpszFmt, pArgList);
    va_end(pArgList);
    if (strContent[strContent.GetLength() - 1] != _T('\n'))
    {
        strContent += _T('\n');
    }

    ::SYSTEMTIME systime;
    ::GetLocalTime(&systime);
    CString strTime;
    strTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d.%03d> "), 
        systime.wYear, systime.wMonth, systime.wDay, 
        systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds);

    CSingleLock singleLock(&ms_cs);

    singleLock.Lock();
    ms_hLogFile.WriteString(strTime + strContent);
    ms_hLogFile.Flush();
    singleLock.Unlock();
}

void CVLPLog::Shutdown()
{
    if (_IsFileValid())
    {
        DumpToLog(_T("<<================ VLPLog Shutdown ==================>>\n"));

        CSingleLock singleLock(&ms_cs);

        singleLock.Lock();
        ms_hLogFile.Close();
        singleLock.Unlock();
    }
}

#endif // _VLPLOG_ON
