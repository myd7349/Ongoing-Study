// An example shows how to make simple things complicated.
#include <iostream>

#include <direct.h>

#include "../ConfigItem.hpp"
#include "../IPv4AddressItem.h"
#include "../ColorRefConverter.hpp"
#ifdef ENABLE_SIMPLEINI
#include "../SimpleIniConfigItemProvider.h"
#else
#include "../IniConfigItemProvider.h"
#endif

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


// <commctrl.h>
#define MAKEIPADDRESS(b1,b2,b3,b4)  ((LPARAM)(((DWORD)(b1)<<24)+((DWORD)(b2)<<16)+((DWORD)(b3)<<8)+((DWORD)(b4))))


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
#ifdef ENABLE_SIMPLEINI
    SimpleIniConfigItemProvider ini(iniPath.c_str());
#else
    IniConfigItemProvider ini(iniPath.c_str());
#endif
    
    BoolItem useIPv6(ini, L"Server", L"UseIPv6", false);
    StringItem ipAddress(ini, L"Server", L"IP", L"localhost");
    IntItem portNumber(ini, L"Server", L"Port", 2026);
    DoubleItem pi(ini, L"", L"PI", 3.14159265358);
    DoubleItem e(ini, L"", L"e", 2.71828);

    IPv4AddressItem ipv4(ini, L"Server", L"IP-2", L"0.0.0.0");

    IN_ADDR in_addr;
    in_addr.s_addr = ntohl(MAKEIPADDRESS(192, 168, 10, 1));
    IPv4AddressItem ipv4_3(ini, L"Server", L"IP-3", in_addr);
    
    ColorRefItem skyBlue(ini, L"Colors", L"Sky", RGB(166, 202, 240));

    if (!PathFileExistsW(iniPath.c_str()))
    {
        useIPv6.Store();
        ipAddress.Store();
        portNumber.Store();
        pi.Store();
        e.Store();
        ipv4.Store();
        ipv4_3.Store();
        skyBlue.Store();
    }
    else
    {
        std::wcout << L"Use IPv6: " << std::boolalpha << useIPv6.GetValue() << std::endl;
        std::wcout << L"IP: " << ipAddress.GetValue() << std::endl;
        std::wcout << L"Port: " << portNumber.GetValue() << std::endl;
        std::wcout << L"PI: " << pi.GetValue() << std::endl;
        std::wcout << L"e: " << e.GetValue() << std::endl;
        std::wcout << L"IP-2: " << ConfigItemConverter<IN_ADDR>().ToString(ipv4.GetValue()) << std::endl;
        std::wcout << L"IP-3: " << ConfigItemConverter<IN_ADDR>().ToString(ipv4_3.GetValue()) << std::endl;
        std::wcout << L"Skyblue: ("
            << GetRValue(skyBlue.GetValue().Color) << ", "
            << GetGValue(skyBlue.GetValue().Color) << ", "
            << GetBValue(skyBlue.GetValue().Color) << ")\n";
    }

    portNumber.SetValue(portNumber.GetValue() + 1);
    portNumber.Store();
    if (portNumber.Load())
        std::cout << "Port: " << portNumber.GetValue() << std::endl;

    portNumber.SetValue(2026);

    std::cout << LoadItem(ini, L"Server", L"Port", 2333) << std::endl;
    std::wcout << ConfigItemConverter<IN_ADDR>().ToString(LoadItem<IN_ADDR>(ini, L"Server", L"IP-2", L"0.0.0.0")) << std::endl;

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
