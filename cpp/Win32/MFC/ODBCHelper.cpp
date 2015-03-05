#include "StdAfx.h"
#include "ODBCHelper.h"

#include <afxdb.h>
#include <afxtempl.h>
#include <atlbase.h>
#include <atlconv.h>

#include <algorithm>
#include <new>

#include <strsafe.h>
#pragma comment(lib, "strsafe.lib")

class CCachedDBConnections
{
    friend class CDBConnection;
public:
    CCachedDBConnections();
    virtual ~CCachedDBConnections();
private:
    CDatabase *GetConnection(const CString &strConnect, BOOL bAutoOpen);
    void RemoveConnection(const CString &strConnect);
private:
    typedef CMap<CString, LPCTSTR, CDatabase *, CDatabase *> CCacheMap;
    CCacheMap m_DBCache;

    static BOOL s_bInitialized;
} g_CachedDBConnections;

BOOL CCachedDBConnections::s_bInitialized = FALSE;

CCachedDBConnections::CCachedDBConnections()
{
    if (!s_bInitialized) 
    {
        s_bInitialized = TRUE;
    }
    else
    {
        throw _T("An instance of CCachedDBConnections already exists");
    }
}

CCachedDBConnections::~CCachedDBConnections()
{
    POSITION p = m_DBCache.GetStartPosition();

    CString strConnect;
    CDatabase *pDB = NULL;
    while (p != NULL)
    {
        m_DBCache.GetNextAssoc(p, strConnect, pDB);
        RemoveConnection(strConnect);
    }
}

CDatabase *CCachedDBConnections::GetConnection(const CString &strConnect, BOOL bAutoOpen)
{
    CCacheMap::CPair *pKeyValPair = m_DBCache.PLookup(strConnect);
    CDatabase *pDB = NULL;
    if (pKeyValPair != NULL)
    {
        pDB = pKeyValPair->value;
    }
    
    if (NULL == pDB)
    {
        try { pDB = new CDatabase; }
        catch (...) { pDB = NULL; }
    }

    if (pDB != NULL && !pDB->IsOpen() && bAutoOpen)
    {
        ATLVERIFY(pDB->OpenEx(strConnect, 
            CDatabase::useCursorLib | CDatabase::noOdbcDialog));
    }

    if (NULL == pKeyValPair)
    {
        m_DBCache[strConnect] = pDB;
    }

    return pDB;
}

void CCachedDBConnections::RemoveConnection(const CString &strConnect)
{
    CCacheMap::CPair *pKeyValPair = m_DBCache.PLookup(strConnect);
    if (pKeyValPair != NULL)
    {
        CDatabase *pDB = NULL;
        std::swap(pDB, pKeyValPair->value);
        if (pDB != NULL)
        {
            if (pDB->IsOpen())
            {
                pDB->Close();
            }

            delete pDB;
            pDB = NULL;
        }

        m_DBCache.RemoveKey(strConnect);
    }
}

CDSN::CDSN(const CString &strDSN, HKEY hKey, const CString &strODBCPath)
{
    CRegKey odbcKey;
    if (odbcKey.Open(hKey, strODBCPath, KEY_READ) != ERROR_SUCCESS)
    {
        throw _T("Open ODBC key failed");
    }
        
    CRegKey dataSourceKey;
    if (dataSourceKey.Open(odbcKey, _T("ODBC Data Sources"), KEY_READ)
        != ERROR_SUCCESS)
    {
        throw _T("Can't interpret Driver name");
    }
    
    _GetStringValue(dataSourceKey, strDSN, m_strDriver);

    CRegKey dsnKey;
    if (dsnKey.Open(odbcKey, strDSN, KEY_READ) != ERROR_SUCCESS)
    {
        throw _T("Invalid DSN");
    }

    _GetStringValue(dsnKey, _T("SERVER"), m_strServer);
    _GetStringValue(dsnKey, _T("UID"), m_strUID);
    _GetStringValue(dsnKey, _T("PWD"), m_strPWD);
    _GetStringValue(dsnKey, _T("DATABASE"), m_strDatabase);
    _GetStringValue(dsnKey, _T("PORT"), m_strPort);
}

CDSN::CDSN(const CString &strDriver, 
    const CString &strServer, const CString &strPort, 
    const CString &strDatabase, const CString &strUID, const CString &strPWD)
    : m_strDriver(strDriver), m_strServer(strServer), m_strPort(strPort), 
      m_strDatabase(strDatabase), m_strUID(strUID), m_strPWD(strPWD)
{
}

void CDSN::_GetStringValue(CRegKey &key, 
    const CString &strValueName, CString &strValue) const
{
    PTSTR pBuf = strValue.GetBuffer(255);
    ULONG ulChars = strValue.GetAllocLength(); // not GetLength
    LONG lRes = key.QueryStringValue(strValueName, pBuf, &ulChars);
    pBuf = NULL;
    strValue.ReleaseBuffer();
    if (lRes != ERROR_SUCCESS)
    {
        throw _T("_GetStringValue failed");
    }
}

CDBConnection::CDBConnection(const CString &strDSN)
{
    try 
    {
        new (&m_DSN) CDSN(strDSN);
        new (this) CDBConnection(m_DSN.GetDriver(),
            m_DSN.GetServer(), m_DSN.GetPort(), 
            m_DSN.GetDatabase(), m_DSN.GetUser(), m_DSN.GetPassword());
    }
    catch (const LPCTSTR &e)
    {
        new (&m_DSN) CDSN();
        ATLTRACE(_T("%s\n"), e);
        m_strConnect.Format(_T("ODBC;DSN=%s"), (LPCTSTR)strDSN);
    }
}

CDBConnection::CDBConnection(const CString &strDriver, 
    const CString &strServer, const CString &strPort, 
    const CString &strDatabase, const CString &strUser, const CString &strPwd)
    : m_DSN(strDriver, strServer, strPort, strDatabase, strUser,strPwd)
{
    // http://bugs.mysql.com/bug.php?id=6704
    // https://www.connectionstrings.com/mysql/
    m_strConnect.Format(_T("DRIVER=%s;SERVER=%s;PORT=%s;DATABASE=%s;UID=%s;PWD=%s;"), 
        strDriver, strServer, strPort, strDatabase, strUser, strPwd);
}

CDBConnection::operator CDatabase *()
{
    return g_CachedDBConnections.GetConnection(m_strConnect, TRUE);
}

CString DBVariantToString(const CDBVariant &variant)
{
    TCHAR szBuf[MAX_PATH] = _T("");

    // wsprintf can not format float point number, so use StringCchVPrintf instead.

    HRESULT hRes = S_OK;

    switch (variant.m_dwType)
    {
    case DBVT_NULL: break;
    case DBVT_BOOL:
        ATLASSERT(FALSE && _T("Not implemented"));
        break;
    case DBVT_UCHAR:
        ATLASSERT(FALSE && _T("Not implemented"));
        break;
    case DBVT_SHORT:
        hRes = StringCchPrintf(szBuf, ARRAYSIZE(szBuf), _T("%d"), variant.m_iVal);
        break;
    case DBVT_LONG:
        hRes = StringCchPrintf(szBuf, ARRAYSIZE(szBuf), _T("%d"), variant.m_lVal);
        break;
    case DBVT_SINGLE:
        hRes = StringCchPrintf(szBuf, ARRAYSIZE(szBuf), _T("%f"), variant.m_fltVal);
        break;
    case DBVT_DOUBLE:
        hRes = StringCchPrintf(szBuf, ARRAYSIZE(szBuf), _T("%d"), variant.m_dblVal);
        break;
    case DBVT_DATE:
        hRes = StringCchPrintf(szBuf, ARRAYSIZE(szBuf), 
            _T("%04d-%02d-%02d %02d:%02d:%02d.%03d"), 
            variant.m_pdate->year, variant.m_pdate->month, variant.m_pdate->day, 
            variant.m_pdate->hour, variant.m_pdate->minute, variant.m_pdate->second, 
            variant.m_pdate->fraction);
        break;
    case DBVT_STRING:
        return *variant.m_pstring;
    case DBVT_BINARY:
        ATLASSERT(FALSE && _T("Not implemented"));
        break;
    case DBVT_ASTRING:
#ifdef UNICODE
        return CA2W(*variant.m_pstringA);
#else
        return *variant.m_pstringA;
#endif
    case DBVT_WSTRING:
#ifdef UNICODE
        return *variant.m_pstringW;
#else
        return CW2A(*variant.m_pstringW);
#endif
    default: ATLASSERT(FALSE); break;
    }

    ATLASSERT(SUCCEEDED(hRes));
    if (FAILED(hRes)) 
    { 
        return _T(""); 
    }

    return szBuf;
}
