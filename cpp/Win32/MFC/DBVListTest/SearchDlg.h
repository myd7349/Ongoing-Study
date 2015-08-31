#pragma once

#include <vector>

// CSearchDlg dialog

class CSearchDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CSearchDlg)

public:
    CSearchDlg(const std::vector<CODBCFieldInfo> &vFieldInfos, CWnd* pParent = NULL);   // standard constructor
    virtual ~CSearchDlg();

    CString GetFilter() const { return m_strFilter; }
    // Dialog Data
    enum { IDD = IDD_SEARCH_DLG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnCbnSelchangeComboFields();
    afx_msg void OnCbnSelchangeComboOperator();
    afx_msg void OnEnChangeEditCriteria();
    DECLARE_MESSAGE_MAP()

private:
    CComboBox m_ctrlFieldsCombox;
    CComboBox m_ctrlOperatorsCombox;
    CEdit m_ctrlCriteriaEdit;

    CString m_strFilter;
    std::vector<CODBCFieldInfo> m_vFieldInfos;

    CString m_strField;
    CString m_strOperator;
    CString m_strCriteria;
};
