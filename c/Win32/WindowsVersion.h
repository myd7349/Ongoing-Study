#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


#ifdef __cplusplus
extern "C"
{
#endif

typedef __success(return >= 0) LONG NTSTATUS;

#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)


// https://github.com/processhacker/processhacker/blob/master/phlib/include/phconfig.h#L24
typedef enum
{
    WINDOWS_ANCIENT     = 0,
    WINDOWS_XP          = 51,
    WINDOWS_SERVER_2003 = 52,
    WINDOWS_VISTA       = 60,
    WINDOWS_7           = 61,
    WINDOWS_8           = 62,
    WINDOWS_8_1         = 63,
    WINDOWS_10          = 100, // TH1
    WINDOWS_10_TH2      = 101,
    WINDOWS_10_RS1      = 102,
    WINDOWS_10_RS2      = 103,
    WINDOWS_10_RS3      = 104,
    WINDOWS_10_RS4      = 105,
    WINDOWS_NEW         = MAXLONG
} WindowsVersion;

NTSYSAPI NTSTATUS NTAPI RtlGetVersion(__out PRTL_OSVERSIONINFOW lpVersionInformation);
WindowsVersion GetWindowsVersion(void);

#define WINDOWS_HAS_UAC (GetWindowsVersion() >= WINDOWS_VISTA)

#ifdef __cplusplus
}
#endif
