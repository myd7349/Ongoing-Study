#include "stdafx.h"
#include "AccelHelper.h"

// MSDN:
// WM_SETHOTKEY
// wParam
//     The low-order word specifies the virtual-key code to associate with the window. 
//     The high-order word can be one or more of the following values. 

DWORD ACCELToDWORD(ACCEL accel)
{
    return (DWORD)MAKELONG(accel.key, accel.fVirt);
}

ACCEL DWORDToACCEL(DWORD dwACCEL)
{
    ACCEL accel;
    accel.key = LOWORD(dwACCEL);
    accel.fVirt = LOBYTE(HIWORD(dwACCEL));
    return accel;
}

DWORD HotKeyToDWORD(WORD wVk, WORD wModifiers)
{
    return (DWORD)MAKELONG(wVk, wModifiers);
}

void DWORDToHotKey(DWORD dwHotKey, WORD &wVk, WORD &wModifiers)
{
    wVk = LOWORD(dwHotKey);
    wModifiers = HIWORD(dwHotKey);
}

ACCEL HotKeyToACCEL(WORD wVk, WORD wModifiers)
{
    ACCEL accel;
    accel.fVirt = FVIRTKEY 
        | ((wModifiers & HOTKEYF_ALT) ? FALT : 0)
        | ((wModifiers & HOTKEYF_CONTROL) ? FCONTROL : 0)
        | ((wModifiers & HOTKEYF_SHIFT) ? FSHIFT : 0);
    accel.key = wVk;

    return accel;
}

void ACCELToHotKey(const ACCEL &accel, WORD &wVk, WORD &wModifiers)
{
    ASSERT(accel.fVirt & FVIRTKEY);

    wVk = accel.key;
    wModifiers = ((accel.fVirt & FALT) ? HOTKEYF_ALT : 0)
        | ((accel.fVirt & FCONTROL) ? HOTKEYF_CONTROL : 0)
        | ((accel.fVirt & FSHIFT) ? HOTKEYF_SHIFT : 0);
}


#define PLUS _T("+")


ACCEL KeyNameToACCEL(const CString &strAccel)
{
    ASSERT((_T("Not Implemented"), FALSE));
    ACCEL accel = {};
    return accel;
}


// CHotKeyCtrl::GetHotKeyName
CString ACCELToKeyName(const ACCEL &accel)
{
    CString strKeyName;

    WORD wVk = 0;
    WORD wModifiers = 0;
    if (accel.fVirt & FVIRTKEY)
    {
        wVk = accel.key;
        wModifiers = (accel.fVirt & (~FVIRTKEY));

        if (wVk != 0 || wModifiers != 0)
        {
            if (wModifiers & FCONTROL)
            {
                strKeyName += CHotKeyCtrl::GetKeyName(VK_CONTROL, FALSE);
                strKeyName += PLUS;
            }

            if (wModifiers & FSHIFT)
            {
                strKeyName += CHotKeyCtrl::GetKeyName(VK_SHIFT, FALSE);
                strKeyName += PLUS;
            }

            if (wModifiers & FALT)
            {
                strKeyName += CHotKeyCtrl::GetKeyName(VK_MENU, FALSE);
                strKeyName += PLUS;
            }

            strKeyName += CHotKeyCtrl::GetKeyName(wVk, FALSE);
        }
    }

    return strKeyName;
}

void KeyNameToHotKey(const CString &strAccel, WORD &wVk, WORD &wModifiers)
{
    ASSERT((_T("Not Implemented"), FALSE));
}

CString HotKeyToKeyName(WORD &wVk, WORD &wModifiers)
{
    CString strKeyName;
    if (wVk != 0 || wModifiers != 0)
    {
        if (wModifiers & HOTKEYF_CONTROL)
        {
            strKeyName += CHotKeyCtrl::GetKeyName(VK_CONTROL, FALSE);
            strKeyName += PLUS;
        }

        if (wModifiers & HOTKEYF_SHIFT)
        {
            strKeyName += CHotKeyCtrl::GetKeyName(VK_SHIFT, FALSE);
            strKeyName += PLUS;
        }

        if (wModifiers & HOTKEYF_ALT)
        {
            strKeyName += CHotKeyCtrl::GetKeyName(VK_MENU, FALSE);
            strKeyName += PLUS;
        }

        strKeyName += CHotKeyCtrl::GetKeyName(wVk, FALSE);
    }

    return strKeyName;
}
