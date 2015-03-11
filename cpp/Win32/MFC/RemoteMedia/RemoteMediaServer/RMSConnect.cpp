// RMSConnect.cpp : implementation file
//

#include "stdafx.h"
#include "RemoteMediaServer.h"
#include "RemoteMediaServerDlg.h"
#include "RMSConnect.h"

// CRMSConnect

CRMSConnect::CRMSConnect()
    : m_bIsDatHdrComing(TRUE)
    , m_pUI(NULL)
{
}

CRMSConnect::~CRMSConnect()
{
}


// CRMSConnect member functions

BOOL CRMSConnect::BoundToUI(CRemoteMediaServerDlg *pUI)
{
    ASSERT(pUI != NULL && pUI->GetSafeHwnd() != NULL);
    if (NULL == pUI || pUI->GetSafeHwnd() == NULL)
    {
        return FALSE;
    }

    m_pUI = pUI;
    return TRUE;
}

void CRMSConnect::OnReceive(int nErrorCode)
{
    ASSERT(*this != INVALID_SOCKET);

    if (m_bIsDatHdrComing)
    {
        RecvDatStrmHeader();
    }
    else
    {
        RecvDatStrm();
    }

    CSocket::OnReceive(nErrorCode);
}

void CRMSConnect::RecvDatStrmHeader()
{
    if (!m_bIsDatHdrComing)
    {
        return;
    }

    cmVLPLogDump(RES_STR(IDS_LOG_DATAHEADER_ARRIVED), this);
    // 接收数据头
    if (Receive(&m_rmRecvStrmH, sizeof(m_rmRecvStrmH))
        != sizeof(m_rmRecvStrmH)) // SOCKET_ERROR
    {
        cmVLPLogDump(RES_STR(IDS_LOG_WRONG_DATAHEADER_SIZE), this);
        return;
    }

    switch (m_rmRecvStrmH.rmDatType.rmc_dat_type)
    {
    case cmRM_DATA_T::RMC_CLOSE: 
        cmVLPLogDump(RES_STR(IDS_LOG_RMC_CLOSE), this);
        Close();
        m_pUI = NULL;
        break;
    default: break;
    }
    
    if (m_rmRecvStrmH.dwDatLen > 0)
    {
        m_bIsDatHdrComing = FALSE;
    }
}

void CRMSConnect::RecvDatStrm()
{
    if (m_bIsDatHdrComing)
    {
        return;
    }

    cmVLPLogDump(RES_STR(IDS_LOG_DATA_ARRIVED), this);
    switch (m_rmRecvStrmH.rmDatType.rmc_dat_type)
    {
    case cmRM_DATA_T::RMC_PREVIEW: 
        {
            cmVLPLogDump(RES_STR(IDS_LOG_RMC_PREVIEW), this);
            cmCBytes tmpMem(m_rmRecvStrmH.dwDatLen);
            if (NULL == tmpMem)
            {
                cmVLPLogDump(RES_STR(IDS_LOG_GET_MEM_FAILED), this);
                cmVLPLogDumpError();
                return;
            }

            int iRecvBytes = Receive(tmpMem, m_rmRecvStrmH.dwDatLen);
            if (iRecvBytes != m_rmRecvStrmH.dwDatLen)
            {
                cmVLPLogDump(RES_STR(IDS_LOG_INVALID_FILE_LEN), this);
                return;
            }

            if (!IsUIBounded())
            {
                return;
            }

            CString strFileName = (LPCTSTR)(void * const)tmpMem;
            cmVLPLogDump(RES_STR(IDS_LOG_FILE_TO_PREVIEW), this, strFileName);
            m_mkvmerge.PrepareRTSPFile(strFileName, this, 300);
        }
        break;
    default: break;
    }

    m_bIsDatHdrComing = TRUE;
}

