// 2013-08-26T09:43+08:00
#pragma once

// CMKVMerge command target
class CMKVMerge;
class CRMSConnect;

typedef struct _TidParms
{
    CMKVMerge *pMkvmerge;
    CRMSConnect *pSockConn;
} TidParms, *PTidParms;

class CMKVMerge : public CObject
{
public:
	CMKVMerge();
	virtual ~CMKVMerge();
public:
    const CString &GetMKVMergePath() const throw()
    {
        return m_strMkvMerge;
    }
    // void SetMKVMergePath(LPCTSTR lpcszPath);
    BOOL Exec(LPCTSTR lpcszSrcFile, LPCTSTR lpcszTargetMkv, 
        const DWORD &dwPreviewLenInSecs, const DWORD &dwStartTimeInSecs);
    void PrepareRTSPFile(const CString &strFileName, 
        CRMSConnect *pSockConn, const DWORD &dwPreviewLenInSecs = 300, 
        const DWORD &dwStartTimeInSecs = 0);
    HANDLE GetRunningProcHandle() { return m_hProcMkvmerge; }
    const CString &GetTargetFileName() const throw() { return m_strTargetMkvFile; }
    void CloseRunningProcHandle();
    void TerminateMkvmergeProc();
private:
    CString m_strMkvMerge; // path of mkvmerge.exe
    HANDLE  m_hProcMkvmerge;

    CString m_strTargetMkvFile;
    CWinThread *m_pChkMkvmergeTid;
    TidParms m_parm;
    static UINT __cdecl CheckIfMkvmergeExit(LPVOID pParam);
};

