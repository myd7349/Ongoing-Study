// SearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DBVListTest.h"
#include "SearchDlg.h"
#include "afxdialogex.h"

#include <algorithm>

BOOL GetCurSelString(const CComboBox &comboBox, CString &strText)
{
    int iCurSel = comboBox.GetCurSel();
    if (iCurSel == CB_ERR)
        return FALSE;

    comboBox.GetLBText(iCurSel, strText);
    return TRUE;
}

void DeleteAllItems(CComboBox &comboBox)
{
    for (int i = 0; i < comboBox.GetCount(); ++i)
        comboBox.DeleteString(0);
}

// CSearchDlg dialog

IMPLEMENT_DYNAMIC(CSearchDlg, CDialogEx)

    CSearchDlg::CSearchDlg(const std::vector<CODBCFieldInfo> &vFieldInfos, CWnd* pParent /*=NULL*/)
    : CDialogEx(CSearchDlg::IDD, pParent), m_vFieldInfos(vFieldInfos)
{
}

CSearchDlg::~CSearchDlg()
{
}

void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_FIELDS, m_ctrlFieldsCombox);
    DDX_Control(pDX, IDC_COMBO_OPERATOR, m_ctrlOperatorsCombox);
    DDX_Control(pDX, IDC_EDIT_CRITERIA, m_ctrlCriteriaEdit);
}


BEGIN_MESSAGE_MAP(CSearchDlg, CDialogEx)
    ON_CBN_SELCHANGE(IDC_COMBO_FIELDS, &CSearchDlg::OnCbnSelchangeComboFields)
    ON_CBN_SELCHANGE(IDC_COMBO_OPERATOR, &CSearchDlg::OnCbnSelchangeComboOperator)
    ON_EN_CHANGE(IDC_EDIT_CRITERIA, &CSearchDlg::OnEnChangeEditCriteria)
END_MESSAGE_MAP()


// CSearchDlg message handlers

BOOL CSearchDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    for (std::size_t i = 0; i < m_vFieldInfos.size(); ++i)
        m_ctrlFieldsCombox.AddString(m_vFieldInfos[i].m_strName);

    m_ctrlOperatorsCombox.EnableWindow(FALSE);
    m_ctrlCriteriaEdit.EnableWindow(FALSE);
    GetDlgItem(IDOK)->EnableWindow(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CSearchDlg::OnOK()
{
    ATLASSERT(!m_strField.IsEmpty() && !m_strOperator.IsEmpty() 
        && !m_strCriteria.IsEmpty());
    m_strFilter.Format(_T("[%s] %s '%s'"), 
        m_strField.GetString(), m_strOperator.GetString(), m_strCriteria.GetString());

    CDialogEx::OnOK();
}

void CSearchDlg::OnCbnSelchangeComboFields()
{
    m_strField.Empty();
    if (!GetCurSelString(m_ctrlFieldsCombox, m_strField)) 
        return;

    auto it = std::find_if(m_vFieldInfos.cbegin(), m_vFieldInfos.cend(), 
        //[&m_strField](const CODBCFieldInfo &fieldInfo) // ???
        [&](const CODBCFieldInfo &fieldInfo) 
    {
        return fieldInfo.m_strName == m_strField;
    });
    if (it == m_vFieldInfos.cend())
        return;

    m_ctrlOperatorsCombox.EnableWindow(!m_strField.IsEmpty());

    DeleteAllItems(m_ctrlOperatorsCombox);

    // I want to implement a various of filters according to the type of the
    // field. That is: for fields with a SQL_VARCHAR type, we will use a
    // text filter here; for fields with a numeric type, however, we will
    // use a number filter.
    // The text filter may supports: equals, contains, starts with, end withs, etc.
    // The number filter may supports: equals, greater than, less than, within, etc.
    // This idea is inspired by the column filtering facility in MS Access. 
    switch (it->m_nSQLType) {
    case SQL_VARCHAR: m_ctrlOperatorsCombox.AddString(_T("=")); break;
    default: ATLASSERT(FALSE && _T("Not implemented.")); break;
    }
}


void CSearchDlg::OnCbnSelchangeComboOperator()
{
    m_strOperator.Empty();
    if (!GetCurSelString(m_ctrlOperatorsCombox, m_strOperator))
        return;

    m_ctrlCriteriaEdit.EnableWindow(!m_strOperator.IsEmpty());
}

void CSearchDlg::OnEnChangeEditCriteria()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialogEx::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.
    m_ctrlCriteriaEdit.GetWindowText(m_strCriteria);
    GetDlgItem(IDOK)->EnableWindow(!m_strCriteria.IsEmpty());
}
