/***************************************************************
 * Name:      RemoteMediaUtility.h
 * Purpose:   
 * Author:    myd7349 (myd7349@gmail.com)
 * Created:   2013-08-20 15:02
 * Copyright: 
 * License:   
 **************************************************************/
#pragma once

#include <afx.h>
#include <afxsock.h>

#include "RemoteMediaListCtrl.h"
#include "VLPLog.h"

#define RES_STR(id) CString(MAKEINTRESOURCE(id))
#define cm_STR(c)           #c
#define cmSTR(c)            cm_STR(c)
#define cmMCAT(l, r)        l##r
#define cmCSTRCAT(l, r)     l r
#define cmFILE              _T(__FILE__)
#define cmLINE              __LINE__
#define cmFUNCTION          _T(__FUNCTION__)
#define cmFUNIN             cmCSTRCAT(_T("(i): "), cmFUNCTION)
#define cmFUNOUT            cmCSTRCAT(_T("(o): "), cmFUNCTION)
ULONGLONG cmGetFileSize(LPCTSTR lpcszFileName);
CString &cmGetReadableFileSize(CString &strSize, const ULONGLONG &ullSizeInBytes);
int cmCompareReadableFileSize(const CString &strLSize, const CString &strRSize);
CString &cmGetModulePathName(CString &strPath, HMODULE hMod = NULL);
CString &cmGetFullPath(CString &strFullPath, const CString &strPath, const CString &strFile);
inline BOOL cmIsValidFileHandle(HANDLE hFile)
{
    return (hFile != INVALID_HANDLE_VALUE);
}
BOOL cmIsExeRunning(LPCTSTR lpcszExeFile);
CString &cmTimeSecs2HMS(CString &strTime, const DWORD &dwTimeInSecs);
CString &cmGetCurDateTime(CString &strDateTime);
BOOL cmGetErrMsg(CString &strMsgContainer, 
    const DWORD &dwErrCode = ::GetLastError(), 
    const WORD &wLangID = ::GetSystemDefaultLangID());
CString &cmGenerateGUID(CString &strGUID);

// RemoteMediaServer默认端口号
enum 
{
    DEF_PORT_NUM = 7349, 
    REV_PORT_NUM = 1028
};

// 在RemoteMedia的Server和Client之间通过TCP传输的数据的类型
union cmRM_DATA_T
{
    // 客户端向服务端发送的数据包的含义
    enum RMC_DATA_T
    {
        RMC_CLIENT = 0x7349FFC0, // 表示一个Client连接请求
        RMC_PREVIEW = 0x7349FFC1, // 表示预览请求（客户端想通过网络串流浏览服务端上多媒体）
        RMC_MEDIA = 0x7349FFC2, // 表示下载请求（客户端想下载服务端上某个多媒体文件）
        RMC_CLOSE = 0x7349FFC3 // 表示Client通知Server客户端想要断开连接
    } rmc_dat_type;

    // 服务端向客户端发送的数据包含义
    enum RMS_DATA_T
    {
        RMS_ACCEPT = 0x1028FFD0, // 表示服务端接受了客户端的连接请求
        RMS_REFUSE = 0x1028FFD1, // 表示服务端拒绝了客户端的连接请求
        RMS_RTSPREADY = 0x1028FFD2, // 表示服务端响应了客户端的RMC_PREVIEW请求并准备提供媒体预览服务
        RMS_RTSPNOTREADY = 0x1028FFD3, // 表示服务端响应了客户端的RMC_PREVIEW请求但无法提供预览服务
        RMS_MEDIA = 0x1028FFD4, // 表示服务端响应了客户端的RMC_MEDIA请求并向客户端发送文件
        RMS_CLOSE = 0x1028FFD5 // 表示服务端程序要退出
    } rms_dat_type;
};

// 不管是服务端程序还是客户端程序，在传输数据的时候，
// 要先传输一个数据头。数据头包含了将要传输的数据的类型以及数据的长度。
struct cmRMDataStreamHeader
{
    cmRM_DATA_T rmDatType; // 数据类型
    DWORD       dwDatLen;  // 数据长度（以字节为单位，数据头大小不包含在内）
};

class cmCIcon
{
public:
    cmCIcon() throw();
    virtual ~cmCIcon();
    BOOL Load(UINT uResID, HINSTANCE hResInst = AfxGetResourceHandle());
    void Free();
    operator HICON() throw()
    {
        return m_hICO;
    }
private:
    cmCIcon(const cmCIcon &);
    cmCIcon &operator=(const cmCIcon &);
private:
    HICON m_hICO;
};

class cmCBytes
{
public:
    cmCBytes(const DWORD &dwSize);
    virtual ~cmCBytes();
    operator void * const() const throw() { return m_lpbyBuf; }
    const DWORD &GetSizeInBytes() const throw() { return m_dwSizeInBytes; }
private:
    DWORD m_dwSizeInBytes;
    BYTE m_byArr[1024 * 512];
    LPBYTE m_lpbyBuf;
};

