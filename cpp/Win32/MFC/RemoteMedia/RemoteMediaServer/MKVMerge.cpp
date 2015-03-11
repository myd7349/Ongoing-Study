// MKVMerge.cpp : implementation file
//

#include "stdafx.h"
#include "RemoteMediaServer.h"
#include "RemoteMediaServerDlg.h"
#include "../RemoteMediaUtility.h"
#include "MKVMerge.h"
#include "RMSConnect.h"

// CMKVMerge

#define MKVMERGE_PROC_TITLE _T("RemoteMediaServer_Mkvmerge")

CMKVMerge::CMKVMerge()
    : m_hProcMkvmerge(NULL)
{
    m_parm.pMkvmerge = NULL;
    m_parm.pSockConn = NULL;
    m_pChkMkvmergeTid = NULL;

#ifdef NDEBUG
    cmGetModulePathName(m_strMkvMerge);
#else
    TCHAR szCurDir[_MAX_PATH];
    _tgetcwd(szCurDir, _countof(szCurDir));
    m_strMkvMerge = szCurDir;
    m_strMkvMerge += _T('\\');
#endif
    m_strMkvMerge += _T("3rdparty\\mkvtoolnix\\mkvmerge.exe");
}

CMKVMerge::~CMKVMerge()
{
    TerminateMkvmergeProc();
    CloseRunningProcHandle();
}

void CMKVMerge::TerminateMkvmergeProc()
{
    if (m_pChkMkvmergeTid != NULL)
    {
        HWND hMkvmerge = ::FindWindow(_T("ConsoleWindowClass"), 
            MKVMERGE_PROC_TITLE);
        if (hMkvmerge != NULL)
        {
            cmVLPLogDump(RES_STR(IDS_LOG_TERMINATE_MKVMERGE_PROC));
#if 1
            // 确保关闭mkvmerge进程后删除未转换完成的文件
            CCriticalSection cs;
            cs.Lock();
            ::SendMessage(hMkvmerge, WM_CLOSE, 0, 0);
            ::DeleteFile(m_strTargetMkvFile);
            cs.Unlock();
#else
            ::TerminateProcess(m_hProcMkvmerge, EXIT_FAILURE);
#endif
            cmVLPLogDump(RES_STR(IDS_LOG_TERMINATE_MKVMERGE_ASS_TID));
            ::WaitForSingleObject(m_pChkMkvmergeTid->m_hThread, INFINITE);
        }
    }
}

/*
void CMKVMerge::SetMKVMergePath(LPCTSTR lpcszPath)
{
    m_strMkvMerge = lpcszPath;
}
*/

// mkvmerge -o RMSTarget.mkv --split parts:00:01:00-00:21:00 MyMedia.rmvb
BOOL CMKVMerge::Exec(LPCTSTR lpcszSrcFile, LPCTSTR lpcszTargetMkv, 
    const DWORD &dwPreviewLenInSecs, const DWORD &dwStartTimeInSecs)
{
    m_strTargetMkvFile = lpcszTargetMkv;

    CloseRunningProcHandle();

    CString strStartTime;
    cmTimeSecs2HMS(strStartTime, dwStartTimeInSecs);
    
    CString strEndTime;
    cmTimeSecs2HMS(strEndTime, dwStartTimeInSecs + dwPreviewLenInSecs);

    CString strMKVMergeCmd;
    strMKVMergeCmd.Format(_T("\"%s\" -o \"%s\"")
        _T(" --split parts:%s-%s \"%s\""), 
        m_strMkvMerge, lpcszTargetMkv, 
        strStartTime, strEndTime, lpcszSrcFile);

    STARTUPINFO si = { sizeof(STARTUPINFO) };
    si.lpTitle = MKVMERGE_PROC_TITLE;
    si.dwFlags = STARTF_USESHOWWINDOW;   
    si.wShowWindow = SW_HIDE;
    PROCESS_INFORMATION pi = { NULL };
    TCHAR szCmdLine[1024];
    ::lstrcpyn(szCmdLine, strMKVMergeCmd, _countof(szCmdLine));

    cmVLPLogDump(RES_STR(IDS_LOG_CREATE_MKVMERGE_PROCESS), szCmdLine);
    
    if (::CreateProcess(NULL, szCmdLine, NULL, NULL, 
        FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
    {
#if 0
        CWaitCursor waitCur;
        ::WaitForSingleObject(pi.hProcess, INFINITE);
        DWORD dwMkvmergeExitCode;
        BOOL bRet = TRUE;
        if (::GetExitCodeProcess(pi.hProcess, &dwMkvmergeExitCode))
        {
            bRet = (0 == dwMkvmergeExitCode);
        }
        ::CloseHandle(pi.hThread);
        ::CloseHandle(pi.hProcess);
        return bRet;
#else
        ::CloseHandle(pi.hThread);
        CCriticalSection cs;
        cs.Lock();
        m_hProcMkvmerge = pi.hProcess;
        cs.Unlock();
        cmVLPLogDump(RES_STR(IDS_LOG_CREATE_MKVMERGE_SUCCESS), m_hProcMkvmerge);
        return TRUE;
#endif
    }
    else
    {
        cmVLPLogDump(RES_STR(IDS_LOG_CREATE_MKVMERGE_FAILED));
        cmVLPLogDumpError();
        return FALSE;
    }
}

void CMKVMerge::PrepareRTSPFile(const CString &strFileName, 
    CRMSConnect *pSockConn, const DWORD &dwPreviewLenInSecs, 
    const DWORD &dwStartTimeInSecs)
{
    cmVLPLogDump(RES_STR(IDS_LOG_PREPARE_PREVIEW));
    if (NULL == pSockConn || INVALID_SOCKET == *pSockConn
        || !pSockConn->IsUIBounded())
    {
        cmVLPLogDump(RES_STR(IDS_LOG_INVALID_SOCKET_OR_UI));
        return;
    }

    CString strFileGuid;
    CRemoteMediaServerDlg *pUI = pSockConn->GetBoundedUI();
    pUI->GetFileGuid(strFileGuid, strFileName);
    if (strFileGuid.IsEmpty())
    {
        cmVLPLogDump(RES_STR(IDS_LOG_RETRIEVE_GUID_FAILED));
        return;
    }

    cmVLPLogDump(RES_STR(IDS_LOG_GUID_OF_THE_FILE_TO_PREVIEW), strFileGuid);
    CString strTargMkvFile;
    cmGetFullPath(strTargMkvFile, pUI->GetMediaServerPath(), 
        strFileGuid + _T(".mkv"));
    cmVLPLogDump(RES_STR(IDS_LOG_TARGET_FILE_TO_PREVIEW), strTargMkvFile);

    cmRMDataStreamHeader rmStrmH;
    rmStrmH.dwDatLen = 0;
#ifdef NDEBUG
    if (::PathFileExists(strTargMkvFile))
    {
        cmVLPLogDump(RES_STR(IDS_LOG_TARGET_FILE_ALREADY_EXIST));
        cmVLPLogDump(RES_STR(IDS_LOG_RESPOND_RMC_CLIENT_OK));
        rmStrmH.rmDatType.rms_dat_type = cmRM_DATA_T::RMS_RTSPREADY;
        pSockConn->Send(&rmStrmH, sizeof(rmStrmH));
    }
    else
#endif
    {
        cmVLPLogDump(RES_STR(IDS_LOG_TARGET_FILE_NOT_FOUND));
        if (Exec(strFileName, strTargMkvFile, dwPreviewLenInSecs, dwStartTimeInSecs))
        {
            m_parm.pMkvmerge = this;
            m_parm.pSockConn = pSockConn;
            // 在线程结束之前，要确保m_parm的有效性。
            TerminateMkvmergeProc();
            cmVLPLogDump(RES_STR(IDS_LOG_CREATE_MKVMERGE_ASS_TID));
            m_pChkMkvmergeTid = AfxBeginThread(CheckIfMkvmergeExit, &m_parm);
        }
        else
        {
            cmVLPLogDump(RES_STR(IDS_LOG_RESPOND_RMC_CLIENT_NOTOK));
            rmStrmH.rmDatType.rms_dat_type = cmRM_DATA_T::RMS_RTSPNOTREADY;
            pSockConn->Send(&rmStrmH, sizeof(rmStrmH));
        }
    }
}

// CMKVMerge member functions

void CMKVMerge::CloseRunningProcHandle()
{
    if (m_hProcMkvmerge != NULL)
    {
        cmVLPLogDump(RES_STR(IDS_LOG_CLOSE_MKVMERGE_PROC_HANDLE), m_hProcMkvmerge);
        CCriticalSection cs;
        cs.Lock();
        ::CloseHandle(m_hProcMkvmerge);
        m_hProcMkvmerge = NULL;
        cs.Unlock();
    }
}

UINT __cdecl CMKVMerge::CheckIfMkvmergeExit(LPVOID pParam)
{
    PTidParms pTidParm = (PTidParms)pParam;
    if (NULL == pTidParm || NULL == pTidParm->pMkvmerge
        || NULL == pTidParm->pSockConn)
    {
        return EXIT_FAILURE;
    }

    cmVLPLogDump(RES_STR(IDS_LOG_MKVMERGE_ASS_TID_CREATED));
    ::WaitForSingleObject(pTidParm->pMkvmerge->GetRunningProcHandle(), 
        INFINITE);

    DWORD dwMkvmergeExitCode;
    cmRMDataStreamHeader rmStrmH;
    rmStrmH.rmDatType.rms_dat_type = cmRM_DATA_T::RMS_RTSPNOTREADY;
    rmStrmH.dwDatLen = 0;

    cmVLPLogDump(RES_STR(IDS_LOG_MKVMERGE_PROC_EXIT));
    
    if (::GetExitCodeProcess(pTidParm->pMkvmerge->GetRunningProcHandle(), &dwMkvmergeExitCode))
    {
        cmVLPLogDump(RES_STR(IDS_LOG_MKVMERGE_EXITCODE), dwMkvmergeExitCode);
        if (0 == dwMkvmergeExitCode 
            && ::PathFileExists(pTidParm->pMkvmerge->GetTargetFileName()))
        {
            rmStrmH.rmDatType.rms_dat_type = cmRM_DATA_T::RMS_RTSPREADY;
        }
    }
    pTidParm->pMkvmerge->CloseRunningProcHandle();
#ifdef _VLPLOG_ON
    if (0 == dwMkvmergeExitCode)
    {
        if (::PathFileExists(pTidParm->pMkvmerge->GetTargetFileName()))
        {
            cmVLPLogDump(RES_STR(IDS_LOG_RESPOND_RMC_CLIENT_OK));
        }
        else
        {
            cmVLPLogDump(RES_STR(IDS_LOG_MKVMERGE_TERMINATED));
        }
    }
    else
    {
        cmVLPLogDump(RES_STR(IDS_LOG_RESPOND_RMC_CLIENT_NOTOK));
    }
#endif
    pTidParm->pSockConn->Send(&rmStrmH, sizeof(rmStrmH));
    return EXIT_SUCCESS;
}
