#include "stdafx.h"
#include "GlobalConfig.h"
#include "Utility.h"

#include <stdlib.h>

class OGlobalConfigHelper
{
    friend class OGlobalConfig;
public:
    OGlobalConfigHelper();
private:
    CString m_strBaseDir;
    CString m_strConfDir;
    CString m_strDataDir;
    CString m_strDBFileName;
};

OGlobalConfigHelper::OGlobalConfigHelper()
{
    m_strBaseDir = GetModulePath(NULL);
    if (!m_strBaseDir.IsEmpty())
    {
        m_strConfDir = JoinPath(LPCTSTR(m_strBaseDir), CONF_SUB_DIR);
        m_strDataDir = JoinPath(LPCTSTR(m_strBaseDir), DATA_SUB_DIR);
        m_strDBFileName = JoinPath(m_strBaseDir, DB_FILE_NAME);
    }
    ATLTRACE2(_T("Base Dir: %s\nConf Dir: %s\nData Dir: %s\nDB File: %s\n"), 
        m_strBaseDir, m_strConfDir, m_strDataDir, m_strDBFileName);
}

static OGlobalConfigHelper gs_GlobalConf;

CString OGlobalConfig::GetBaseDir()
{
    return gs_GlobalConf.m_strBaseDir;
}

CString OGlobalConfig::GetConfDir()
{
    return gs_GlobalConf.m_strConfDir;
}

CString OGlobalConfig::GetDataDir()
{
    return gs_GlobalConf.m_strDataDir;
}

CString OGlobalConfig::GetDBFileName()
{
    return gs_GlobalConf.m_strDBFileName;
}