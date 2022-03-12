#include "MultiMonitor.h"

#include <cassert>


BOOL CALLBACK MonitorEnumProc(
    HMONITOR hMonitor,
    HDC hdcMonitor,
    LPRECT lprcMonitor,
    LPARAM dwData
    )
{
    UNREFERENCED_PARAMETER(hdcMonitor);
    UNREFERENCED_PARAMETER(lprcMonitor);

    auto monitorInfoVector = reinterpret_cast<std::vector<MONITORINFOEX> *>(dwData);
    assert(monitorInfoVector != nullptr);

    MONITORINFOEX mi {};
    mi.cbSize = sizeof(MONITORINFOEX);

    GetMonitorInfo(hMonitor, &mi);

    monitorInfoVector->push_back(std::move(mi));

    return TRUE;
}



bool GetAllMonitorInfos(std::vector<MONITORINFOEX> &monitorInfos)
{
    monitorInfos.clear();

    return !!EnumDisplayMonitors(
        NULL, NULL, MonitorEnumProc, reinterpret_cast<LPARAM>(&monitorInfos));
}


void GetAllDisplayDevices(std::map<std::wstring, DisplayDeviceInfo> &displayDevices)
{
    displayDevices.clear();

    DisplayDeviceInfo ddi {};
    ddi.cb = sizeof(DISPLAY_DEVICE);

    for (int i = 0; EnumDisplayDevices(NULL, i, &ddi, 0); ++i)
    {
        ddi.dwDevNum = i;
        displayDevices[ddi.DeviceName] = ddi;
    }
}


// References:
// https://github.com/mpc-hc/mpc-hc/blob/develop/src/mpc-hc/MultiMonitor.h
