#pragma once

#ifdef _WINDOWS_
# error See [0]
#endif

#include <WinSock2.h>
#include <WS2tcpip.h>


#ifdef _MSC_VER
# pragma comment(lib, "Ws2_32.lib")
# pragma warning(disable: 4996)
#endif

#include "ConfigItemConverter.hpp"


bool operator==(IN_ADDR lhs, IN_ADDR rhs)
{
    return lhs.s_addr == rhs.s_addr;
}


bool operator!=(IN_ADDR lhs, IN_ADDR rhs)
{
    return !operator==(lhs, rhs);
}


template <>
inline IN_ADDR ConfigItemConverter<IN_ADDR, wchar_t>::FromString(StringT s, bool &ok, IN_ADDR defaultValue) const
{
    if (s == nullptr)
    {
        ok = false;
        return defaultValue;
    }

    IN_ADDR ip = { 0 };
#if defined(RtlIpv4StringToAddress)
    ok = RtlIpv4StringToAddressW(s, FALSE, NULL, &ip) == NO_ERROR;
#elif defined(InetPton)
    ok = InetPtonW(AF_INET, s, &ip) == 1;
#else
# error inet_aton
#endif
    return ok ? ip : defaultValue;
}


template <>
inline std::wstring ConfigItemConverter<IN_ADDR, wchar_t>::ToString(IN_ADDR ip) const
{
    wchar_t ipString[16] = L"";

#if defined(RtlIpv4AddressToString)
    RtlIpv4AddressToStringW(&ip, ipString);
    return ipString;
#elif defined(InetNtop)
    if (InetNtopW(AF_INET, &ip, ipString, ARRAYSIZE(ipString)) != NULL)
        return ipString;
    else
        return L"";
#else
# error inet_ntoa
#endif
}


// References:
// [0] https://stackoverflow.com/questions/22517036/socket-errors-cant-get-functions-in-winsock2-h
// [1] https://stackoverflow.com/questions/1372480/c-redefinition-header-files-winsock2-h
