// VLCWrapper.cpp : implementation file
//

#include "stdafx.h"
#include "RemoteMediaClient.h"
#include "VLCWrapper.h"
#include "../RemoteMediaUtility.h"


// CVLCWrapper

CVLCWrapper::CVLCWrapper()
{
    CRegKey regKey;

    if (regKey.Open(HKEY_LOCAL_MACHINE, 
        _T("Software\\VideoLAN\\VLC"), KEY_READ)
        == ERROR_SUCCESS)
    {
        TCHAR szVLCPath[_MAX_PATH];
        ULONG ulBufSize = _countof(szVLCPath);
        if (regKey.QueryStringValue(NULL, szVLCPath, 
            &ulBufSize) == ERROR_SUCCESS)
        {
            m_strVLCPlayer = szVLCPath;
        }
        regKey.Close();
    }
}

CVLCWrapper::~CVLCWrapper()
{
}


// CVLCWrapper member functions
BOOL CVLCWrapper::IsVLCReady() const
{
    return !m_strVLCPlayer.IsEmpty();
}

BOOL CVLCWrapper::Preview(const CString &strRTSP)
{
    cmVLPLogDump(RES_STR(IDS_LOG_CREATING_VLC_PROC));

    if (!IsVLCReady())
    {
        cmVLPLogDump(RES_STR(IDS_LOG_VLC_NOTREADY));
        return FALSE;
    }

    CString strCmdLine;
    strCmdLine.Format(_T("\"%s\" %s"), 
        m_strVLCPlayer, strRTSP);

    TCHAR szCmdLine[1024];
    ::lstrcpyn(szCmdLine, strCmdLine, _countof(szCmdLine));

    cmVLPLogDump(RES_STR(IDS_LOG_VLC_CMDLINE), szCmdLine);

    STARTUPINFO si = { sizeof(STARTUPINFO) };
    si.dwFlags = STARTF_USESHOWWINDOW;   
    si.wShowWindow = SW_SHOWNORMAL;
    PROCESS_INFORMATION pi = { NULL };

    // CWaitCursor waitCur;

    if (::CreateProcess(NULL, szCmdLine, NULL, NULL, 
        FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
    {
#if 0
        BOOL bRet = TRUE;
        ::WaitForSingleObject(pi.hProcess, INFINITE);
        DWORD dwExitCode;
        if (::GetExitCodeProcess(pi.hProcess, &dwExitCode))
        {
            bRet = (0 == dwExitCode);
        }
        ::CloseHandle(pi.hThread);
        ::CloseHandle(pi.hProcess);
        return bRet;
#else
        cmVLPLogDump(RES_STR(IDS_LOG_CREATE_VLC_PROC_SUCCESS));
        return TRUE;
#endif
    }
    else
    {
        cmVLPLogDump(RES_STR(IDS_LOG_CREATE_VLC_PROC_FAILED));
        cmVLPLogDumpError();
        return FALSE;
    }
}


// References:
// https://github.com/rocksdanister/lively/tree/dev-v1.0-fluent-netcore/src/livelywpf/libVLCPlayer
