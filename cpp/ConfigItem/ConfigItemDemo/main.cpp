// An example shows how to make simple things complicated.
#include <iostream>

#include <direct.h>

#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include "../ConfigItem.hpp"
#include "../IniConfigItemProvider.h"


std::wstring GetCwd()
{
    std::wstring cwd;

    wchar_t *buffer = _wgetcwd(NULL, 0);
    if (buffer != NULL)
    {
        cwd = std::wstring(buffer);
        std::free(buffer);
        buffer = NULL;
    }

    return cwd;
}


int wmain(int argc, wchar_t *argv[])
{
    std::wstring cwd = GetCwd();
    std::wcout << L"CWD: " << cwd << std::endl;

    std::wstring appPath = argv[0];
    std::wstring::size_type lastPathSepPos = appPath.find_last_of(L"\\");
    if (lastPathSepPos != std::wstring::npos)
        appPath = appPath.substr(0, lastPathSepPos + 1);

    std::wcout << "App Path: " << appPath << std::endl;

    std::wstring iniPath = appPath + L"Config.ini";
    IniConfigItemProvider ini(iniPath.c_str());
    
    StringItem ipAddress(ini, L"Server", L"IP", L"localhost");
    IntItem portNumber(ini, L"Server", L"Port", 2026);
    DoubleItem pi(ini, L"", L"PI", 3.14159265358);
    DoubleItem e(ini, L"", L"e", 2.71828);

    if (!PathFileExists(iniPath.c_str()))
    {
        ipAddress.Store();
        portNumber.Store();
        pi.Store();
        e.Store();
    }
    else
    {
        std::wcout << L"IP: " << ipAddress.GetValue() << std::endl;
        std::cout << "Port: " << portNumber.GetValue() << std::endl;
        std::cout << "PI: " << pi.GetValue() << std::endl;
        std::cout << "e: " << e.GetValue() << std::endl;
    }

    portNumber.SetValue(portNumber.GetValue() + 1);
    portNumber.Store();
    if (portNumber.Load())
        std::cout << "Port: " << portNumber.GetValue() << std::endl;

    portNumber.SetValue(2026);

    std::cout << LoadItem(ini, L"Server", L"Port", 2333) << std::endl;

    return 0;
}
