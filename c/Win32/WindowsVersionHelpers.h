#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


#ifdef __cplusplus
extern "C"
{
#endif

#define WINDOWS_NT4      0x0400
#define WINDOWS_WIN2K    0x0500
#define WINDOWS_WINXP    0x0501
#define WINDOWS_WS03     0x0502
#define WINDOWS_WIN6     0x0600
#define WINDOWS_VISTA    0x0600
#define WINDOWS_WS08     0x0600
#define WINDOWS_LONGHORN 0x0600
#define WINDOWS_WIN7     0x0601
#define WINDOWS_WIN8     0x0602
#define WINDOWS_WINBLUE  0x0603
#define WINDOWS_WIN10    0x0A00

BOOL IsWindowsXPOrGreater();
BOOL IsWindowsXPSP1OrGreater();
BOOL IsWindowsXPSP2OrGreater();
BOOL IsWindowsXPSP3OrGreater();
BOOL IsWindowsVistaOrGreater();
BOOL IsWindowsVistaSP1OrGreater();
BOOL IsWindowsVistaSP2OrGreater();
BOOL IsWindows7OrGreater();
BOOL IsWindows7SP1OrGreater();
BOOL IsWindows8OrGreater();
BOOL IsWindows8Point1OrGreater();
BOOL IsWindows10OrGreater();

BOOL IsWindowsServer();

#define WINDOWS_HAS_UAC (IsWindowsVistaOrGreater())

#ifdef __cplusplus
}
#endif
