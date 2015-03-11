// 2013-08-23T26:06+08:00
// RemoteMediaClientDlg.h : 头文件
//

#pragma once

#include <afxlistctrl.h>
#include <afxcmn.h>
#include <afxwin.h>

#include "VLCWrapper.h"
#include "../RemoteMediaUtility.h"
#include "RMCSocket.h"

// CRemoteMediaClientDlg 对话框
class CRemoteMediaClientDlg : public CDialogEx
{
// 构造
public:
	CRemoteMediaClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_REMOTEMEDIACLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
    cmCIcon m_icoConn;
    cmCIcon m_icoDisConn;
    cmCIcon m_icoPreview;
    cmCIcon m_icoAbout;
    cmCIcon m_icoExit;
private:
    CVLCWrapper m_vlcPlayer;
    CRMCSocket m_socketConn;
    DWORD m_dwRetryTimes; // 与服务端连接失败后设置重连次数
    CString m_strFileName; // 要预览的文件的名称
    CString m_strServIP;
private:
    CRemoteMediaListCtrl m_ctrlPlaylist;
    CIPAddressCtrl m_ctrlServIPAddr;
    CButton m_btnConn;
    CButton m_btnPreview;
    CButton m_btnAbout;
    CButton m_btnExit;
    CEdit m_edtPortNum;
    CButton m_chkUseDefPort;
protected:
    void InitUI();
    void LoadSettings();
    void SaveSettings();
    CString &RetrieveServIP(CString &strServIP);
public:
    void ConnectToServer();
    void DisConnectWithServer();
    void TryToHandshake();
    void LoadPlaylist();
    void PreviewSelectedFile();
public:
    afx_msg void OnDestroy();
    afx_msg void OnBnClickedBtnConnect();
    afx_msg void OnBnClickedBtnPreview();
    afx_msg void OnBnClickedBtnHelp();
    afx_msg LRESULT OnNcHitTest(CPoint point);
    afx_msg void OnBnClickedChkUsedefport();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
};
