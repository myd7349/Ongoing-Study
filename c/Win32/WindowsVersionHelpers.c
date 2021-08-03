#include "WindowsVersionHelpers.h"


BOOL IsWinVersionOrGreater(DWORD id, WORD wServicePackMajor)
{
    WORD wMajorVersion = HIBYTE(id);
    WORD wMinorVersion = LOBYTE(id);

    OSVERSIONINFOEXW osvi = { sizeof(osvi), 0, 0, 0, 0,{ 0 }, 0, 0 };
    DWORDLONG const dwlConditionMask =
        VerSetConditionMask(
            VerSetConditionMask(
                VerSetConditionMask(0, VER_MAJORVERSION, VER_GREATER_EQUAL),
                VER_MINORVERSION, VER_GREATER_EQUAL),
            VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL);

    osvi.dwMajorVersion = wMajorVersion;
    osvi.dwMinorVersion = wMinorVersion;
    osvi.wServicePackMajor = wServicePackMajor;

    return VerifyVersionInfoW(&osvi, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, dwlConditionMask) != FALSE;
}

BOOL IsWindowsXPOrGreater()      {  return IsWinVersionOrGreater(WINDOWS_WINXP, 0);}
BOOL IsWindowsXPSP1OrGreater()   {  return IsWinVersionOrGreater(WINDOWS_WINXP, 1);}
BOOL IsWindowsXPSP2OrGreater()   {  return IsWinVersionOrGreater(WINDOWS_WINXP, 2);}
BOOL IsWindowsXPSP3OrGreater()   {  return IsWinVersionOrGreater(WINDOWS_WINXP, 3);}
BOOL IsWindowsVistaOrGreater()   {  return IsWinVersionOrGreater(WINDOWS_VISTA, 0);}
BOOL IsWindowsVistaSP1OrGreater(){  return IsWinVersionOrGreater(WINDOWS_VISTA, 1);}
BOOL IsWindowsVistaSP2OrGreater(){  return IsWinVersionOrGreater(WINDOWS_VISTA, 2);}
BOOL IsWindows7OrGreater()       {  return IsWinVersionOrGreater(WINDOWS_WIN7,  0);}
BOOL IsWindows7SP1OrGreater()    {  return IsWinVersionOrGreater(WINDOWS_WIN7,  1);}
BOOL IsWindows8OrGreater()       {  return IsWinVersionOrGreater(WINDOWS_WIN8,  0);}
BOOL IsWindows8Point1OrGreater() {  return IsWinVersionOrGreater(WINDOWS_WINBLUE, 0); }
BOOL IsWindows10OrGreater()      {  return IsWinVersionOrGreater(WINDOWS_WIN10, 0); }

BOOL IsWindowsServer()
{
    OSVERSIONINFOEXW osvi = { sizeof(osvi), 0, 0, 0, 0,{ 0 }, 0, 0, 0, VER_NT_WORKSTATION };
    DWORDLONG const dwlConditionMask = VerSetConditionMask(0, VER_PRODUCT_TYPE, VER_EQUAL);
    return !VerifyVersionInfoW(&osvi, VER_PRODUCT_TYPE, dwlConditionMask);
}


// References:
// https://stackoverflow.com/questions/34235151/get-windows-version
// https://github.com/dahall/Vanara/blob/56cda5a8f4d6648563651996d99f471f9e49e56f/PInvoke/Kernel32/VersionHelpers.cs#L49
