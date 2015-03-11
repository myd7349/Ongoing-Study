// 2013-08-23T09:03+08:00
#pragma once

#include "../RemoteMediaUtility.h"

class CRemoteMediaClientDlg;

class CRMCSocket : public CSocket
{
public:
	CRMCSocket();
	virtual ~CRMCSocket();
    virtual void OnReceive(int nErrorCode);
public:
    BOOL BoundToUI(CRemoteMediaClientDlg *pUI);
    BOOL IsUIBounded()
    {
        return m_pUI != NULL;
    }
    BOOL IsHandshakeOK();
protected:
    void RecvDatStrmHeader();
    void RecvDatStrm();
private:
    CRemoteMediaClientDlg *m_pUI;
    BOOL m_bIsDatHdrComing; // 接下来要接收的数据是否是数据头
    cmRMDataStreamHeader m_rmRecvStrmH; // 最后一次接收到的数据头
    BOOL m_bIsHandShakeOK; // 记录客户端和服务端是否握手成功
};


