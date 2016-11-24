// 2016-11-24T10:05+08:00
#pragma once

DWORD ACCELToDWORD(ACCEL accel);
ACCEL DWORDToACCEL(DWORD dwACCEL);

DWORD HotKeyToDWORD(WORD wVk, WORD wModifiers);
void DWORDToHotKey(DWORD dwHotKey, WORD &wVk, WORD &wModifiers);

ACCEL HotKeyToACCEL(WORD wVk, WORD wModifiers);
void ACCELToHotKey(const ACCEL &accel, WORD &wVk, WORD &wModifiers);

ACCEL KeyNameToACCEL(const CString &strAccel);
CString ACCELToKeyName(const ACCEL &accel);

void KeyNameToHotKey(const CString &strAccel, WORD &wVk, WORD &wModifiers);
CString HotKeyToKeyName(WORD &wVk, WORD &wModifiers);
