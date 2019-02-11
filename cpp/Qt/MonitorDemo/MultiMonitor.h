#pragma once

#include <map>
#include <string>
#include <vector>

#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
//#include <multimon.h>


struct DisplayDeviceInfo : public DISPLAY_DEVICE
{
    DWORD dwDevNum;
};


bool GetAllMonitorInfos(std::vector<MONITORINFOEX> &monitorInfos);
void GetAllDisplayDevices(std::map<std::wstring, DisplayDeviceInfo> &displayDevices);
