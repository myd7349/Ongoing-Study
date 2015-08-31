#include "stdafx.h"
#include "EmployeeSet.h"
#include "../Utility.h"

IMPLEMENT_DYNAMIC(CEmployeeSet, CRecordset)

    CEmployeeSet::CEmployeeSet(CDatabase* pdb)
    : CRecordset(pdb)
{
    m_nFields = 7;
    m_nDefaultType = dynaset;
}

void CEmployeeSet::SetFilter(CString strCurQuery, BOOL bUpdate)
{
    // convenience function to set the SQL filter for the query
    if (strCurQuery == m_strFilter && !bUpdate)
        return;

    CWaitCursor wait;

    m_strFilter.SetString(strCurQuery);
    if (!IsOpen())
        Open();
    Requery();

    // update record counts
    while (!IsEOF())
        MoveNext();
}


void CEmployeeSet::SetSort(LPCTSTR pszSortField)
{
    // convenience function to set the SQL sort for the query

    m_strSort = pszSortField;
    if (IsOpen())
    {
        CWaitCursor wait;
        Requery();
    }
}


// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CEmployeeSet::GetDefaultConnect()
{
    CString strAppPath = GetModulePath();
    CString strDBPath = JoinPath(strAppPath, _T("employee.mdb"));
    CString strConnStr;

#if 0
    CString strFileDSNPath = JoinPath(strAppPath, _T("employee.mdb.dsn"));
    strConnStr.Format(
        _T("DBQ=%s;DefaultDir=%s;Driver={Microsoft Access Driver (*.mdb)};")
        _T("DriverId=281;FIL=MS Access;FILEDSN=%s;MaxBufferSize=2048;MaxScanRows=8;")
        _T("PageTimeout=5;SafeTransactions=0;Threads=3;UID=admin;UserCommitSync=Yes;")
        , strDBPath.GetString(), strAppPath.GetString(), strFileDSNPath.GetString());
#else
    strConnStr.Format(_T("Driver={Microsoft Access Driver (*.mdb)};DBQ=%s;"), strDBPath.GetString());
#endif
    return strConnStr;
}

CString CEmployeeSet::GetDefaultSQL()
{
    return _T("[Employee8]");
}

void CEmployeeSet::DoFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);
    // Macros such as RFX_Text() and RFX_Int() are dependent on the
    // type of the member variable, not the type of the field in the database.
    // ODBC will try to automatically convert the column value to the requested type
    RFX_Text(pFX, _T("[Email]"), m_EmpItem.m_Email);
    RFX_Text(pFX, _T("[Name]"), m_EmpItem.m_Name);
    RFX_Text(pFX, _T("[Phone]"), m_EmpItem.m_Phone);
    RFX_Text(pFX, _T("[Location]"), m_EmpItem.m_Location);
    RFX_Text(pFX, _T("[Title]"), m_EmpItem.m_Title);
    RFX_Text(pFX, _T("[Department]"), m_EmpItem.m_Department);
    RFX_Text(pFX, _T("[Division]"), m_EmpItem.m_Division);
}
/////////////////////////////////////////////////////////////////////////////
// CEmployeeSet diagnostics

#ifdef _DEBUG
void CEmployeeSet::AssertValid() const
{
    CRecordset::AssertValid();
}

void CEmployeeSet::Dump(CDumpContext& dc) const
{
    CRecordset::Dump(dc);
}
#endif //_DEBUG


