#include "stdafx.h"
#include "MD5Digest.h"

//#include <WinCrypt.h>

#include <iomanip>
#include <sstream>

// http://www.codeproject.com/Questions/58270/MD-and-VC

CMD5Digest::CMD5Digest()
{
    if (CryptAcquireContext(&m_hCryptProv, NULL, NULL, PROV_RSA_FULL, NULL))
    {
        if (CryptCreateHash(m_hCryptProv, CALG_MD5, NULL, NULL, &m_hCryptHash))
        {
            m_bValid = TRUE;
        }
        else
        {
            m_bValid = FALSE;
        }
    }
    else
    {
        m_bValid = FALSE;
    }

    m_bMoreData = m_bValid;
}

CMD5Digest::~CMD5Digest()
{
    if (m_hCryptHash != NULL)
    {
        CryptDestroyHash(m_hCryptHash);
    }

    if (m_hCryptProv != NULL)
    {
        CryptReleaseContext(m_hCryptProv, 0);
    }
}

BOOL CMD5Digest::Update(BYTE *pbyData, DWORD dwDataLen)
{
    if (m_bMoreData)
    {
        ATLASSERT(m_hCryptProv != NULL && m_hCryptHash != NULL);

        if (!CryptHashData(m_hCryptHash, pbyData, dwDataLen, 0))
        {
            m_bValid = FALSE;
            m_bMoreData = FALSE;
        }
    }

    return m_bMoreData;
}

BOOL CMD5Digest::GetDigest(BYTE (&abyMD5Digest)[MD5_DIGEST_LEN])
{
    ATLASSERT(MD5_DIGEST_LEN == 16);

    if (m_bValid)
    {
        // MSDN上说，获取digest结果之前，需要先以HP_HASHSIZE来调用CryptGetHashParam以
        // 获取digest的长度。但是由于MD5的digest为16个字节长度，所以，这里省略了这一步。
        DWORD dwHashLen = sizeof(abyMD5Digest);
        if (!CryptGetHashParam(m_hCryptHash, HP_HASHVAL, abyMD5Digest, &dwHashLen, 0))
        {
            m_bValid = FALSE;
        }

        if (m_bMoreData)
        {
            m_bMoreData = FALSE;
        }
    }

    return m_bValid;
}

CString CMD5Digest::GetHexDigest(BOOL bUpperCase)
{
    CString strHexDigest;
    BYTE abyMD5Digest[MD5_DIGEST_LEN];

    if (GetDigest(abyMD5Digest))
    {
#ifdef _UNICODE
        std::wostringstream oss;
#else
        std::ostringstream oss;
#endif

        oss << std::hex << std::setfill(_T('0'));
        for (unsigned int i = 0; i < ARRAYSIZE(abyMD5Digest); ++i)
        {
            oss << std::setw(2) << static_cast<int>(abyMD5Digest[i]);
        }

        strHexDigest = oss.str().c_str();
    }

    return strHexDigest;
}

CString CMD5Digest::GetFileDigest(const CString &strFileName, BOOL bUpperCase)
{
    CString strHexDigest;

    CFile fileSource;
    if (fileSource.Open(strFileName, CFile::modeRead | CFile::shareDenyWrite))
    {
        CMD5Digest md5;
        
        BYTE abyBuf[4096];
        UINT uBytesReaded;
        while ((uBytesReaded = fileSource.Read(abyBuf, sizeof(abyBuf))) != 0
            && md5.Update(abyBuf, uBytesReaded)) 
        {
        }

        strHexDigest = md5.GetHexDigest(bUpperCase);
        fileSource.Close();
    }
    
    return strHexDigest;
}

BOOL CMD5Digest::CheckFileDigest(const CString &strFileName, const CString &strMD5HexDigest)
{
    return strMD5HexDigest.CompareNoCase(GetFileDigest(strFileName)) == 0;
}

BOOL CMD5Digest::CompareFileDigest(const CString &strLeftFile, const CString &strRightFile)
{
    return GetFileDigest(strLeftFile).CompareNoCase(GetFileDigest(strRightFile)) == 0;
}

