// 2015-08-27T13:58+08:00

#pragma once

struct EmployeeItem {
    CStringW m_Email;
    CStringW m_Name;
    CStringW m_Phone;
    CStringW m_Location;
    CStringW m_Title;
    CStringW m_Department;
    CStringW m_Division;
};

typedef EmployeeItem *PEmployeeItem;

// Generated by Visual Studio MFC ODBC Source Wizard...

class CEmployeeSet : public CRecordset
{
public:
    CEmployeeSet(CDatabase* pDatabase = NULL);
    DECLARE_DYNAMIC(CEmployeeSet)

    void SetFilter(CString strCurQuery, BOOL bUpdate);
    void SetSort(LPCTSTR pszSortField);

    // Field/Param Data

    // The string types below (if present) reflect the actual data type of the
    // database field - CStringA for ANSI datatypes and CStringW for Unicode
    // datatypes. This is to prevent the ODBC driver from performing potentially
    // unnecessary conversions.  If you wish, you may change these members to
    // CString types and the ODBC driver will perform all necessary conversions.
    // (Note: You must use an ODBC driver version that is version 3.5 or greater
    // to support both Unicode and these conversions).

    EmployeeItem m_EmpItem;

    // Overrides
    // Wizard generated virtual function overrides
public:
    virtual CString GetDefaultConnect();	// Default connection string

    virtual CString GetDefaultSQL(); 	// default SQL for Recordset
    virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

    // Implementation
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};


