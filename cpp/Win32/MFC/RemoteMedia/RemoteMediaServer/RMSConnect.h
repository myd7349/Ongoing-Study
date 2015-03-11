// 2013-08-25T18::04+08:00
#pragma once

#include "../RemoteMediaUtility.h"
#include "MKVMerge.h"

class CRemoteMediaServerDlg;

class CRMSConnect : public CSocket
{
public:
	CRMSConnect();
	virtual ~CRMSConnect();
    virtual void OnReceive(int nErrorCode);
public:
    BOOL BoundToUI(CRemoteMediaServerDlg *pUI);
    BOOL IsUIBounded()
    {
        return m_pUI != NULL;
    }
    CRemoteMediaServerDlg *GetBoundedUI() { return m_pUI; }
protected:
    void RecvDatStrmHeader();
    void RecvDatStrm();
private:
    CRemoteMediaServerDlg *m_pUI;
    CMKVMerge m_mkvmerge;
    BOOL m_bIsDatHdrComing; // 接下来要接收的数据是否是数据头
    cmRMDataStreamHeader m_rmRecvStrmH; // 最后一次接收到的数据头
};
