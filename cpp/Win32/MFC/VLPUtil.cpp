#include "stdafx.h"
#include "VLPUtil.h"

CString &cmGetLastError(CString &strMsgContainer, 
    const DWORD &dwErrCode, 
    const WORD &wLangID)
{
    LPVOID lpvErrMsgBuf = NULL;

    if (::FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER 
        | FORMAT_MESSAGE_FROM_SYSTEM 
        | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, dwErrCode, wLangID,
        (LPTSTR)&lpvErrMsgBuf, 0, NULL) != 0)
    {
        strMsgContainer = (LPTSTR)lpvErrMsgBuf;
        ::LocalFree(lpvErrMsgBuf);
        return strMsgContainer;
    }
    else
    {
        strMsgContainer.Format(
            _T("Invoke FormatMessage failed in %s(%d)."), 
            cmFUNCTION, ::GetLastError());
        return strMsgContainer;
    }
}