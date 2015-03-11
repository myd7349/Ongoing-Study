// Live555MediaServer.cpp : implementation file
//

#include "stdafx.h"
#include "RemoteMediaServer.h"
#include "..\RemoteMediaUtility.h"
#include "Live555MediaServer.h"

#define LIVE555_MEDIA_SERVER_FILENAME _T("live555MediaServer.exe")

// CLive555MediaServer

CLive555MediaServer::CLive555MediaServer()
#ifdef ENABLE_TERMINATE_LIVE555
    : m_hLive555Proc(NULL)
#endif
{
#ifdef NDEBUG
    cmGetModulePathName(m_strLive555Path);
#else
    TCHAR szCurDir[_MAX_PATH];
    _tgetcwd(szCurDir, _countof(szCurDir));
    m_strLive555Path = szCurDir;
    m_strLive555Path += _T('\\');
#endif
    m_strLive555Path += _T("3rdparty\\live555\\");
}

CLive555MediaServer::~CLive555MediaServer()
{
    Terminate();
}

void CLive555MediaServer::SetLive555Path(LPCTSTR lpcszPath)
{
    m_strLive555Path = lpcszPath;
}

BOOL CLive555MediaServer::Start()
{
    CString strLive555MediaServer;
    cmGetFullPath(strLive555MediaServer, 
        m_strLive555Path, LIVE555_MEDIA_SERVER_FILENAME);
    WIN32_FIND_DATA fd;
    HANDLE hFileFind = ::FindFirstFile(strLive555MediaServer, &fd);

    if (!cmIsValidFileHandle(hFileFind))
    {
        cmVLPLogDump(RES_STR(IDS_LOG_LIVE555_NOT_FOUND), 
            CString(_T("3rdparty\\live555\\")) + LIVE555_MEDIA_SERVER_FILENAME);
        return FALSE;
    }
#if 0
    // TODO: 这里让我很费解。
    if (::GetFileType(hFileFind) != FILE_TYPE_DISK)
    {
        ::FindClose(hFileFind);
        return FALSE;
    }
#endif
    ::FindClose(hFileFind);

#ifdef ENABLE_TERMINATE_LIVE555
    if (m_hLive555Proc != NULL)
#else
    if (cmIsExeRunning(LIVE555_MEDIA_SERVER_FILENAME))    
#endif
    {
        return TRUE;
    }

    STARTUPINFO si = { sizeof(STARTUPINFO) };
    si.dwFlags = STARTF_USESHOWWINDOW;   
    si.wShowWindow = SW_HIDE;
    PROCESS_INFORMATION pi = { NULL };
    // 我想要隐藏live555mediaserver.exe的主窗口，那为什么我不用
    // CREATE_NO_WINDOW而是先用CREATE_NEW_CONSOLE然后隐藏窗体呢？
    // 这是因为我想要在主程序退出时以一种比较温和的方式结束创建的进程
    // ——通过向live555mediaserver发送WM_CLOSE消息。
    // 如果使用CREATE_NO_WINDOW，则调用FindWindow找不到live555mediaserver
    // 的窗体（因为NO WINDOW），而用CREATE_NEW_CONSOLE并指定
    // STARTUPINFO中的wShowWindow为FALSE就可以实现创建窗体，但把窗体隐藏起来
    // 。这样不影响FindWindow和SendMessage的调用。从而可以比较温和地终止
    // live555mediaserver进程。
    if (::CreateProcess(strLive555MediaServer, NULL, NULL, NULL, 
        FALSE, CREATE_NEW_CONSOLE, NULL, m_strLive555Path, &si, &pi))
    {
        ::CloseHandle(pi.hThread);
#ifdef ENABLE_TERMINATE_LIVE555
        m_hLive555Proc = pi.hProcess;
#else
        ::CloseHandle(pi.hProcess);
#endif
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void CLive555MediaServer::Terminate()
{
#ifdef ENABLE_TERMINATE_LIVE555
    if (m_hLive555Proc != NULL)
    {
        ::TerminateProcess(m_hLive555Proc, EXIT_SUCCESS);
        m_hLive555Proc = NULL;
    }
#else
    CString strLive555MediaServer;
    cmGetFullPath(strLive555MediaServer, 
        m_strLive555Path, LIVE555_MEDIA_SERVER_FILENAME);
    HWND hLive555Wnd = ::FindWindow(_T("ConsoleWindowClass"), 
        strLive555MediaServer);
    if (::IsWindow(hLive555Wnd))
    {
        ::SendMessage(hLive555Wnd, WM_CLOSE, 0, 0);
    }
#endif
}


// CLive555MediaServer member functions
