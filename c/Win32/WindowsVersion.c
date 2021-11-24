#include "WindowsVersion.h"

// https://github.com/processhacker/processhacker/blob/43f99d5a351a5091dffecdbaa8f22bb10f53dce3/lib/lib32/ntdll.lib
#pragma comment(lib, "ntdll.lib")


WindowsVersion GetWindowsVersion(void)
{
    RTL_OSVERSIONINFOEXW versionInfo;
    ULONG majorVersion;
    ULONG minorVersion;
    ULONG buildVersion;

    versionInfo.dwOSVersionInfoSize = sizeof(RTL_OSVERSIONINFOEXW);

    if (!NT_SUCCESS(RtlGetVersion((PRTL_OSVERSIONINFOW)&versionInfo)))
    {
        return WINDOWS_NEW;
    }

    majorVersion = versionInfo.dwMajorVersion;
    minorVersion = versionInfo.dwMinorVersion;
    buildVersion = versionInfo.dwBuildNumber;

    if (majorVersion == 5 && minorVersion < 1 || majorVersion < 5)
    {
        return WINDOWS_ANCIENT;
    }
    /* Windows XP */
    else if (majorVersion == 5 && minorVersion == 1)
    {
        return WINDOWS_XP;
    }
    /* Windows Server 2003 */
    else if (majorVersion == 5 && minorVersion == 2)
    {
        return WINDOWS_SERVER_2003;
    }
    /* Windows Vista, Windows Server 2008 */
    else if (majorVersion == 6 && minorVersion == 0)
    {
        return WINDOWS_VISTA;
    }
    /* Windows 7, Windows Server 2008 R2 */
    else if (majorVersion == 6 && minorVersion == 1)
    {
        return WINDOWS_7;
    }
    // Windows 8, Windows Server 2012
    else if (majorVersion == 6 && minorVersion == 2)
    {
        return WINDOWS_8;
    }
    // Windows 8.1, Windows Server 2012 R2
    else if (majorVersion == 6 && minorVersion == 3)
    {
        return WINDOWS_8_1;
    }
    // Windows 10, Windows Server 2016
    else if (majorVersion == 10 && minorVersion == 0)
    {
        switch (buildVersion)
        {
        case 10240:
            return WINDOWS_10;
            break;
        case 10586:
            return WINDOWS_10_TH2;
            break;
        case 14393:
            return WINDOWS_10_RS1;
            break;
        case 15063:
            return WINDOWS_10_RS2;
            break;
        case 16299:
            return WINDOWS_10_RS3;
            break;
        case 17134:
            return WINDOWS_10_RS4;
            break;
        default:
            return buildVersion > 17134 ? WINDOWS_10_RS4 : WINDOWS_10;
            break;
        }
    }
    else
    {
        return WINDOWS_NEW;
    }
}


// References:
// https://github.com/processhacker/processhacker/blob/master/phlib/global.c#160
//     PhInitializeWindowsVersion
//
// http://www.cppblog.com/free2000fly/archive/2008/07/23/56904.html
// https://msdn.microsoft.com/en-us/library/windows/desktop/ms724429(v=vs.85).aspx
// https://stackoverflow.com/questions/457872/how-do-you-check-the-windows-version-in-win32-at-runtime
// https://stackoverflow.com/questions/34235151/get-windows-version
// https://github.com/wixtoolset/issues/issues/4061/
// https://stackoverflow.com/questions/27246562/how-to-get-the-os-version-in-win8-1-as-getversion-getversionex-are-deprecated
// https://github.com/novotnyllc/OSVersionHelper
