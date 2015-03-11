// 2013-08-23T16:59+08:00
#pragma once

#include "../RemoteMediaUtility.h"

class CRMSConnect;
class CRemoteMediaServerDlg;

class CRMSSocket : public CSocket
{
public:
	CRMSSocket();
	virtual ~CRMSSocket();
    virtual void OnAccept(int nErrorCode);
public:
    void FreeClientList();
    CRMSConnect *GetUnusedSockObj();
    BOOL BoundToUI(CRemoteMediaServerDlg *pUI);
    BOOL IsUIBounded()
    {
        return m_pUI != NULL;
    }
    void UpdateClientsPlaylist();
protected:
    void SendPlaylist(CRMSConnect *pSock);
private:
    CList<CRMSConnect *> m_sockClientList;
    CRemoteMediaServerDlg *m_pUI;
};


