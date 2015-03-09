// 2014-05-19T08:52+08:00
#pragma once

#include <atlstr.h>

#if defined(NDEBUG)
#  define CONF_SUB_DIR _T("conf")
#  define DATA_SUB_DIR _T("dat")
#  define DB_FILE_NAME _T("db\\proj.mdb") 
#else
#  define CONF_SUB_DIR _T("../conf")
#  define DATA_SUB_DIR _T("../dat")
#  define DB_FILE_NAME _T("../db/proj.mdb") 
#endif

class OGlobalConfig
{
public:
    static CString GetBaseDir();
    static CString GetConfDir();
    static CString GetDataDir();
    static CString GetDBFileName();
};


