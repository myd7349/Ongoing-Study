#include "stdafx.h"
#include "FileMapping.h"

cmCFileMapping::cmCFileMapping()
    : m_hFileMapping(NULL)
    , m_lpvBeg(NULL)
    , m_lpvEnd(NULL)
{
}

cmCFileMapping::~cmCFileMapping()
{
    Detach();
}

BOOL cmCFileMapping::Attach(const CString &strFileName)
{
    Detach();

    CFileException fileExp;
    if (!m_hFile.Open(strFileName, CFile::modeRead, &fileExp))
    {
        goto _ExitOnFailure;
    }

    ULARGE_INTEGER uliFileSize;
    uliFileSize.QuadPart = m_hFile.GetLength();
    m_hFileMapping = ::CreateFileMapping(HANDLE(m_hFile), 
        NULL, PAGE_READONLY, uliFileSize.u.HighPart, 
        uliFileSize.u.LowPart, _T("RemoteMediaPlaylist"));
    if (NULL == m_hFileMapping)
    {
        goto _ExitOnFailure;
    }

    m_lpvBeg = ::MapViewOfFile(m_hFileMapping, 
        FILE_MAP_READ, 0U, 0U, 0U);
    if (NULL == m_lpvBeg)
    {
        goto _ExitOnFailure;
    }

    m_lpvEnd = reinterpret_cast<char *>(m_lpvBeg) 
        + uliFileSize.QuadPart;
    return TRUE;

_ExitOnFailure:
    Detach();
    return FALSE;
}

void cmCFileMapping::Detach()
{
    if (m_lpvBeg != NULL)
    {
        ::UnmapViewOfFile(m_lpvBeg);
        m_lpvBeg = m_lpvEnd = NULL;
    }

    if (m_hFileMapping != NULL)
    {
        ::CloseHandle(m_hFileMapping);
        m_hFileMapping = NULL;
    }

    if (m_hFile.m_hFile != CFile::hFileNull)
    {
        m_hFile.Close();
    }
}

ULONGLONG cmCFileMapping::GetFileSize()
{
    return (PBYTE)m_lpvEnd - (PBYTE)m_lpvBeg;
}

cmCFileMapping::operator LPVOID()
{
    return m_lpvBeg;
}

