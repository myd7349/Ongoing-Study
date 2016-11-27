// 2016-11-24 10:05
#pragma once

#include "HNFC.h"

HNFC_API DWORD ACCELToDWORD(ACCEL accel);
HNFC_API ACCEL DWORDToACCEL(DWORD dwACCEL);

HNFC_API DWORD HotKeyToDWORD(WORD wVk, WORD wModifiers);
HNFC_API void DWORDToHotKey(DWORD dwHotKey, WORD &wVk, WORD &wModifiers);

HNFC_API ACCEL HotKeyToACCEL(WORD wVk, WORD wModifiers);
HNFC_API void ACCELToHotKey(const ACCEL &accel, WORD &wVk, WORD &wModifiers);

HNFC_API ACCEL KeyNameToACCEL(const CString &strAccel);
HNFC_API CString ACCELToKeyName(const ACCEL &accel);

HNFC_API void KeyNameToHotKey(const CString &strAccel, WORD &wVk, WORD &wModifiers);
HNFC_API CString HotKeyToKeyName(WORD &wVk, WORD &wModifiers);


// Check if the input is a valid combination of known modifiers
HNFC_API BOOL IsValidACCELModifiers(WORD wACCELModifiers);
HNFC_API BOOL IsValidHotKeyModifiers(WORD wHotKeyModifiers);

HNFC_API BOOL IsValidACCEL(ACCEL accel);
HNFC_API BOOL IsValidHotKey(WORD wVk, WORD wModifiers);

HNFC_API WORD HotKeyModifiersToACCELModifiers(WORD wModifiers);
HNFC_API WORD ACCELModifiersToHotKeyModifiers(WORD wModifiers);

