
// DBVListTestDlg.h : header file
//

#pragma once

#include <vector>

#include "EmployeeSet.h"

#ifndef USE_ITEM_CACHE_HINT
# define USE_ITEM_CACHE_HINT (0)
#endif

#if USE_ITEM_CACHE_HINT
# include <vector>
#endif

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
    PEmployeeItem RetrieveItem(int iItem);
#if USE_ITEM_CACHE_HINT
    void PrepareCache(int iFrom, int iTo);
#endif
    void UpdateFilterAndRecordCount(CString strCurQuery);
    void InitListControl();
    std::size_t GetFieldInfos(std::vector<CODBCFieldInfo> &vFieldInfos);
    inline CString QuotedValue(const CString &strValue)
    {
        return _T('\'') + strValue + _T('\'');
    }

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnLvnColumnclickEmpList(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnLvnGetdispinfoEmpList(NMHDR *pNMHDR, LRESULT *pResult);
#if USE_ITEM_CACHE_HINT
    afx_msg void OnLvnOdcachehintEmpList(NMHDR *pNMHDR, LRESULT *pResult);
#endif
    afx_msg void OnLvnOdfinditemEmpList(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnLvnEndlabeleditEmpList(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedBtnAll();
    afx_msg void OnBnClickedBtnSearch();
    afx_msg void OnBnClickedBtnModify();
    afx_msg void OnBnClickedBtnDelete();
    DECLARE_MESSAGE_MAP()

private:
    CEmployeeSet m_DBVListSet;
    CListCtrl m_ctrlEmpList;
    BOOL m_bASC;

#if USE_ITEM_CACHE_HINT
    std::vector<EmployeeItem> m_vMainCache; // main cache
    std::vector<EmployeeItem> m_vEndAreaCache; // cache of items at the end of the list
    int m_iMainCacheStart; // index of the first item in the main cache
    int m_iEndAreaCacheStart; // index of the first item in the end cache
#endif
};
