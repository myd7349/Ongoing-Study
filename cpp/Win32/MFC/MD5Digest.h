/***************************************************************
 * Name:      MD5Digest.h
 * Purpose:   
 * Author:    myd7349
 * Created:   2014-08-21 09:28
 * Copyright: 
 * License:   
 **************************************************************/

#pragma once

#include <atlstr.h>

class CMD5Digest
{
public:
    enum { MD5_DIGEST_LEN = 16 };

    CMD5Digest();
    ~CMD5Digest();

    BOOL Update(BYTE *pbyData, DWORD dwDataLen);
    // 调用GetDigest、GetHexDigest后不能再调用Update。
    BOOL GetDigest(BYTE (&abyMD5Digest)[MD5_DIGEST_LEN]);
    CString GetHexDigest(BOOL bUpperCase = FALSE);

    static CString GetFileDigest(const CString &strFileName, BOOL bUpperCase = FALSE);
    static BOOL CheckFileDigest(const CString &strFileName, const CString &strMD5HexDigest);
    static BOOL CompareFileDigest(const CString &strLeftFile, const CString &strRightFile);
private:
    CMD5Digest(const CMD5Digest &);
    CMD5Digest &operator=(const CMD5Digest &);
private:
    BOOL m_bValid;
    BOOL m_bMoreData;

    HCRYPTPROV m_hCryptProv;
    HCRYPTHASH m_hCryptHash;
};

