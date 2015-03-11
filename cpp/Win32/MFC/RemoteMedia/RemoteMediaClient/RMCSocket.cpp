// RMCSocket.cpp : implementation file
//

#include "stdafx.h"
#include "RemoteMediaClient.h"
#include "RMCSocket.h"
#include "RemoteMediaClientDlg.h"

// CRMCSocket

CRMCSocket::CRMCSocket()
    : m_pUI(NULL)
    , m_bIsDatHdrComing(TRUE)
    , m_bIsHandShakeOK(FALSE)
{
}

CRMCSocket::~CRMCSocket()
{
}

BOOL CRMCSocket::BoundToUI(CRemoteMediaClientDlg *pUI)
{
    ASSERT(pUI != NULL && pUI->GetSafeHwnd() != NULL);
    if (NULL == pUI || pUI->GetSafeHwnd() == NULL)
    {
        return FALSE;
    }

    m_pUI = pUI;
    return TRUE;
}

BOOL CRMCSocket::IsHandshakeOK()
{
    return m_bIsHandShakeOK;
}

void CRMCSocket::RecvDatStrmHeader()
{
    if (!m_bIsDatHdrComing)
    {
        return;
    }

    cmVLPLogDump(RES_STR(IDS_LOG_DATA_HEADER_COMING), this);
    // 接收数据头
    if (Receive(&m_rmRecvStrmH, sizeof(m_rmRecvStrmH))
        != sizeof(m_rmRecvStrmH)) // SOCKET_ERROR
    {
        cmVLPLogDump(RES_STR(IDS_LOG_WRONG_DATAHEADER_SIZE), this);
        return;
    }

    switch (m_rmRecvStrmH.rmDatType.rms_dat_type)
    {
    case cmRM_DATA_T::RMS_ACCEPT:
        m_bIsHandShakeOK = TRUE;
        cmVLPLogDump(RES_STR(IDS_LOG_RMS_ACCEPT), this);
        break;
    case cmRM_DATA_T::RMS_RTSPREADY:
        cmVLPLogDump(RES_STR(IDS_LOG_RMS_RTSPREADY), this);
        if (IsUIBounded())
        {
            cmVLPLogDump(RES_STR(IDS_LOG_PREVIEWING), this);
            m_pUI->PreviewSelectedFile();
        }
        break;
    case cmRM_DATA_T::RMS_CLOSE:
        if (IsUIBounded())
        {
            cmVLPLogDump(RES_STR(IDS_LOG_RMS_CLOSE), this);
            m_pUI->DisConnectWithServer();
            m_bIsHandShakeOK = FALSE;
        }
        break;
    default: break;
    }

    if (m_rmRecvStrmH.dwDatLen > 0)
    {
        m_bIsDatHdrComing = FALSE;
    }
}

void CRMCSocket::RecvDatStrm()
{
    if (m_bIsDatHdrComing)
    {
        return;
    }

    switch (m_rmRecvStrmH.rmDatType.rms_dat_type)
    {
    case cmRM_DATA_T::RMS_ACCEPT:
        {
            cmCBytes tmpMem(m_rmRecvStrmH.dwDatLen);
            if (NULL == tmpMem)
            {
                cmVLPLogDump(RES_STR(IDS_LOG_GET_MEM_FAILED), this);
                return;
            }

            int iRecvBytes = Receive(tmpMem, tmpMem.GetSizeInBytes());
            if (iRecvBytes != (DWORD)m_rmRecvStrmH.dwDatLen)
            {
                cmVLPLogDump(RES_STR(IDS_LOG_INVALID_FILE_LEN), this);
                return;
            }

            CFile filePlaylist;
            if (!filePlaylist.Open(DEFAULT_PLAYLIST_FILENAME, 
                CFile::modeCreate | CFile::modeWrite))
            {
                cmVLPLogDump(RES_STR(IDS_LOG_CREATE_PLAYLIST_FAILED), this);
                return;
            }
            filePlaylist.Write(tmpMem, iRecvBytes);
            filePlaylist.Close();
            if (IsUIBounded())
            {
                m_pUI->LoadPlaylist();
            }
        }
        break;
    default: break;
    }

    m_bIsDatHdrComing = TRUE;
}

void CRMCSocket::OnReceive(int nErrorCode)
{
    ASSERT(*this != INVALID_SOCKET);

    cmVLPLogDump(RES_STR(IDS_LOG_DATA_RECEIVED), this);

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
