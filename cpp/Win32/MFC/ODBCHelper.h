// 2014-11-25T10:34+08:00
// By myd7349
#pragma once

#include <atlstr.h>

class CDatabase;
class CDBVariant;

class CDSN
{
    friend class CDBConnection;
public:
    explicit CDSN(const CString &strDSN, HKEY hKey = HKEY_CURRENT_USER, 
        const CString &strODBCPath = _T("Software\\ODBC\\ODBC.INI"));
    CDSN(const CString &strDriver, 
        const CString &strServer, const CString &strPort, 
        const CString &strDatabase, const CString &strUID, const CString &strPWD);

    CString GetDriver() const { return m_strDriver; }
    CString GetServer() const { return m_strServer; }
    CString GetUser() const { return m_strUID; }
    CString GetPassword() const { return m_strPWD; }
    CString GetDatabase() const { return m_strDatabase; }
    CString GetPort() const { return m_strPort; }
    CString GetServerAndPort() const { return m_strServer + _T(':') + m_strPort; }
private:
    CDSN() {}
    void _GetStringValue(CRegKey &key, 
        const CString &strValueName, CString &strValue) const;
private:
    CString m_strDriver;
    CString m_strServer;
    CString m_strUID;
    CString m_strPWD;
    CString m_strDatabase;
    CString m_strPort;
};

class CDBConnection
{
public:
    explicit CDBConnection(const CString &strDSN);
    CDBConnection(const CString &strDriver, 
        const CString &strServer, const CString &strPort, 
        const CString &strDatabase, const CString &strUser, 
        const CString &strPwd);
    operator CDatabase *();
    CDatabase *operator->() { return (CDatabase *)(*this); };
    CDSN &GetDSN() { return m_DSN; }
private:
    CString m_strConnect;
    CDSN    m_DSN;
};

CString DBVariantToString(const CDBVariant &variant);

