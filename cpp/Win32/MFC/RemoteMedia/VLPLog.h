/* 
** FileName: VLPLog.h
** Purpose : Log module of project VLP, using for runtime diagnose.
**           CVLPLog is only a wrapper of a CStdioFile object.
**           I intend to make it thread-safe, which hasn't been tested yet.
** Author  : myd7349<myd7349@gmail.com>
** DateTime: 2013-03-12 14:59
** TODO    : I may define a class derived from CArchive to write log message as 
**           CArchive has rewritten "operator<<" for most of the built-in types.
** HOWTO   : <TODO: Usage of this class here>
*/

#pragma once

#ifdef _VLPLOG_ON
  #undef _VLPLOG_ON
#endif

#define _VLPLOG_ON // comment out this line to turn off log system

#ifdef _VLPLOG_ON

class CVLPLog
{
public:
	CVLPLog();
	virtual ~CVLPLog();

    static BOOL Startup(LPCTSTR lpszLogFileName);
    static void CDECL DumpToLog(LPCTSTR lpszFmt, ...);
    static void Shutdown();
    /*
    // if you want to CVLPLog work with CArchive, then ...
    static CStdioFile &GetLogFileHandle() 
    {
        return ms_hLogFile;
    }
    */
protected:
    // Prevent you from creating a CVLPLog object
    virtual void _Dummy() = 0;
    static BOOL _IsFileValid()
    {
        return (ms_hLogFile.m_hFile != CStdioFile::hFileNull);
    }
private:
    CVLPLog(const CVLPLog &);
    CVLPLog &operator=(const CVLPLog &);

    static CCriticalSection ms_cs;
    static CStdioFile       ms_hLogFile;
};

#define cmVLPLogStartup(szLogFileName) \
    CVLPLog::Startup(szLogFileName)
#define cmVLPLogShutdown()  \
    atexit(CVLPLog::Shutdown)
#define cmVLPLogDump(fmt, ...) \
    CVLPLog::DumpToLog(fmt, __VA_ARGS__)
#define cmVLPLogDumpError() \
    do \
    { \
        DWORD dwErrCode = ::GetLastError(); \
        CString strErrMsg; \
        cmGetErrMsg(strErrMsg, dwErrCode); \
        cmVLPLogDump(_T("%s(%d) %s(%d): %s"), \
            cmFILE, cmLINE, _T("Error"), dwErrCode, \
            strErrMsg); \
    } while (0)

#else

#define cmVLPLogStartup(szLogFileName) (TRUE)
#define cmVLPLogShutdown()             ((void)0)
#define cmVLPLogDump(fmt, ...)         ((void)0)
#define cmVLPLogDumpError()            ((void)0)

#endif // _VLPLOG_ON
