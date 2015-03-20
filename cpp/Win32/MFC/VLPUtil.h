/* 
** FileName: VLPUtil.h
** Purpose : Some wonderful utilities(macros, functions and so on).
** Author  : myd7349
** DateTime: 2013-03-12 13:00
** TODO    : Nothing.
** HOWTO   : <TODO: Usage of this header file here>
*/

#pragma once

#define cmResStr(id)        (CString(MAKEINTRESOURCE(id)))
#define cmIsNull(ptr)       (NULL == (ptr))
#define cmIsValidPtr(ptr)   (!cmIsNull((ptr)))
// ** Caution: You should not use AtlAlignUp(Down)
// cmAlignUp has the risk of overflow.
#define cmAlignUp(num, n)   (((num) + (n) - 1) / (n) * (n))
#define cmAlignDown(num, n) ((num) / (n) * (n))
#define cm_STR(c)           #c
#define cmSTR(c)            cm_STR(c)
#define cmMCAT(l, r)        l##r
#define cmCSTRCAT(l, r)     l r
#define cmFILE              _T(__FILE__)
#define cmLINE              __LINE__
#define cmFUNCTION          _T(__FUNCTION__)
#define cmFUNIN             cmCSTRCAT(_T("(i): "), cmFUNCTION)
#define cmFUNOUT            cmCSTRCAT(_T("(o): "), cmFUNCTION)

inline CRect cmRect2CRect(const Gdiplus::Rect &rc)
{
    return CRect(rc.X, rc.Y, 
        rc.X + rc.Width, rc.Y + rc.Height);
}

inline Gdiplus::Rect cmCRect2Rect(const CRect &rc)
{
    return Gdiplus::Rect(rc.left, rc.top, 
        rc.Width(), rc.Height());
}

CString &cmGetLastError(CString &strMsgContainer, 
    const DWORD &dwErrCode = ::GetLastError(), 
    const WORD &wLangID = MAKELANGID(LANG_CHINESE_SIMPLIFIED,
                                     SUBLANG_CHINESE_SIMPLIFIED));

/*
inline bool IsNull(const void * const pcvcPtr)
{
    return (pcvcPtr == nullptr);
}

inline bool IsValidPtr(const void * const pcvcPtr)
{
    return (pcvcPtr != nullptr);
}
*/
