
// VirtualListCtrlDemoDlg.h : header file
//

#pragma once


// CVirtualListCtrlDemoDlg dialog
class CVirtualListCtrlDemoDlg : public CDialogEx
{
// Construction
public:
	CVirtualListCtrlDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_VLISTCTRLDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
