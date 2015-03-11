// 2013-08-21T17:54+08:00
#pragma once

class cmCFileMapping
{
public:
    cmCFileMapping();
    virtual ~cmCFileMapping();
    BOOL Attach(const CString &strFileName);
    void Detach();
    ULONGLONG GetFileSize();
    operator LPVOID();
private:
    cmCFileMapping(const cmCFileMapping &);
    cmCFileMapping &operator=(const cmCFileMapping &);
private:
    CFile m_hFile;
    HANDLE m_hFileMapping;

    LPVOID m_lpvBeg;
    LPVOID m_lpvEnd;
};
