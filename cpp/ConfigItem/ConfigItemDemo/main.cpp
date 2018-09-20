// An example shows how to make simple things complicated.
#include <iostream>

#include <direct.h>

#include "../ConfigItem.hpp"
#include "../IniConfigItemProvider.h"
#include "../IPv4AddressItem.h"

#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")


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

    bool ok;
    IPv4AddressItem ipv4(ini, L"Server", L"IP-2",
        ConfigItemConverter<IN_ADDR>().FromString(L"0.0.0.0", ok));

    if (!PathFileExists(iniPath.c_str()))
    {
        ipAddress.Store();
        portNumber.Store();
        pi.Store();
        e.Store();
        ipv4.Store();
    }
    else
    {
        std::wcout << L"IP: " << ipAddress.GetValue() << std::endl;
        std::wcout << L"Port: " << portNumber.GetValue() << std::endl;
        std::wcout << L"PI: " << pi.GetValue() << std::endl;
        std::wcout << L"e: " << e.GetValue() << std::endl;
        std::wcout << L"IP-2: " << ConfigItemConverter<IN_ADDR>().ToString(ipv4.GetValue()) << std::endl;
    }

    portNumber.SetValue(portNumber.GetValue() + 1);
    portNumber.Store();
    if (portNumber.Load())
        std::cout << "Port: " << portNumber.GetValue() << std::endl;

    portNumber.SetValue(2026);

    std::cout << LoadItem(ini, L"Server", L"Port", 2333) << std::endl;

    {
        IN_ADDR inAddr = ipv4.GetValue();
        inAddr.s_net++;
        inAddr.s_host++;
        inAddr.s_lh++;
        inAddr.s_impno++;
        ipv4.SetValue(inAddr);
    }

    return 0;
}
