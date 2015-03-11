// 2013-08-24T14:16+08:00
// RemoteMediaServerDlg.h : 头文件
//

#pragma once
#include <afxlistctrl.h>
#include <afxext.h>
#include <afxwin.h>

#include "../RemoteMediaUtility.h"
#include "RMSSocket.h"
#include "Live555MediaServer.h"
#include "MKVMerge.h"

class CRMSConnect;

// CRemoteMediaServerDlg 对话框
class CRemoteMediaServerDlg : public CDialogEx
{
// 构造
public:
	CRemoteMediaServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_REMOTEMEDIASERVER_DIALOG };

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
    cmCIcon m_icoAdd;
    cmCIcon m_icoRemove;
    cmCIcon m_icoHelp;
    cmCIcon m_icoOK;
private:
    CRemoteMediaListCtrl m_ctrlPlaylist;
    CButton m_btnAdd;
    CButton m_btnRemove;
    CButton m_btnHelp;
    CButton m_btnOK;
    CMenu   m_menuAdd;
private:
    CRMSSocket m_socketListen;

    CLive555MediaServer m_live555;
private:
    void InitUI();
protected:
    afx_msg void OnBnClickedBtnAdd();
    afx_msg void OnBnClickedBtnRemove();
    afx_msg void OnBnClickedBtnHelp();
    afx_msg void OnDestroy();
    virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnNcHitTest(CPoint point);
public:
    CString &GetFileGuid(CString &strGuid, const CString &strFileName);
    const CString &GetMediaServerPath() const throw();
};
