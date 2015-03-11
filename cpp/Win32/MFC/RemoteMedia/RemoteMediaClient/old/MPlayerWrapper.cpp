// MPlayerWrapper.cpp : implementation file
//

#include "stdafx.h"
#include "RemoteMediaClient.h"
#include "../RemoteMediaUtility.h"
#include "MPlayerWrapper.h"


// CMPlayerWrapper

CMPlayerWrapper::CMPlayerWrapper()
{
#ifdef NDEBUG
    cmGetModulePathName(m_strMPlayer);
#else
    TCHAR szCurDir[_MAX_PATH];
    _tgetcwd(szCurDir, _countof(szCurDir));
    m_strMPlayer = szCurDir;
    m_strMPlayer += _T('\\');
#endif
    m_strMPlayer += _T("3rdparty\\MPlayer\\mplayer.exe");
}

CMPlayerWrapper::~CMPlayerWrapper()
{
}

BOOL CMPlayerWrapper::Preview(const CString &strRTSP)
{
    CString strCmdLine;
    strCmdLine.Format(_T("\"%s\" -rtsp-stream-over-tcp \"%s\""), 
        m_strMPlayer, strRTSP);

    TCHAR szCmdLine[1024];
    ::lstrcpyn(szCmdLine, strCmdLine, _countof(szCmdLine));

    STARTUPINFO si = { sizeof(STARTUPINFO) };
    si.dwFlags = STARTF_USESHOWWINDOW;   
    si.wShowWindow = SW_SHOWNORMAL;
    PROCESS_INFORMATION pi = { NULL };

    CWaitCursor waitCur;

    if (::CreateProcess(NULL, szCmdLine, NULL, NULL, 
        FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
    {
        ::WaitForSingleObject(pi.hProcess, INFINITE);
        DWORD dwExitCode;
        BOOL bRet = TRUE;
        if (::GetExitCodeProcess(pi.hProcess, &dwExitCode))
        {
            bRet = (0 == dwExitCode);
        }
        ::CloseHandle(pi.hThread);
        ::CloseHandle(pi.hProcess);
        return bRet;
    }
    else
    {
        return FALSE;
    }
}


// CMPlayerWrapper member functions
