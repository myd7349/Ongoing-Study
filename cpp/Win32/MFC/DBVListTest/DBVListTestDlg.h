
// DBVListTestDlg.h : header file
//

#pragma once

#include <vector>

#include "EmployeeSet.h"

// CDBVListTestDlg dialog
class CDBVListTestDlg : public CDialogEx
{
// Construction
public:
	CDBVListTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DBVLISTTEST_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

    void GetDispInfo(LVITEM* pItem);
    void UpdateFilter(CString strCurQuery, BOOL bUpdate = FALSE);
    void InitListControl();

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnLvnColumnclickEmpList(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnLvnGetdispinfoEmpList(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnLvnOdcachehintEmpList(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnLvnOdfinditemEmpList(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedBtnSearch();
    afx_msg void OnBnClickedBtnDelete();
    DECLARE_MESSAGE_MAP()

private:
    std::size_t GetFieldInfos(std::vector<CODBCFieldInfo> &vFieldInfos);

    CEmployeeSet m_DBVListSet;
    CListCtrl m_ctrlEmpList;
};
