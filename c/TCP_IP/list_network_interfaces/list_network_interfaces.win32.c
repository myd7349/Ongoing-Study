#include <locale.h>
#include <stdlib.h>

#include "tcpip.h"


PIP_ADAPTER_ADDRESSES GetAdaptersAddressesEx(ULONG family, ULONG flags)
{
    PIP_ADAPTER_ADDRESSES pAddresses = NULL;
    ULONG bufferSize = 10240;
    DWORD result;

    while (1)
    {
        pAddresses = malloc(bufferSize);
        if (pAddresses == NULL)
            return NULL;

        result = GetAdaptersAddresses(family, flags, NULL, pAddresses, &bufferSize);
        if (result == ERROR_SUCCESS)
        {
            break;
        }
        else
        {
            free(pAddresses);
            pAddresses = NULL;

            if (result != ERROR_BUFFER_OVERFLOW)
                break; 
        }
    }

    return pAddresses;
}


#define FreeAdaptersAddresses(p) free((p))


int _tmain(int argc, _TCHAR *argv[])
{
    PIP_ADAPTER_ADDRESSES pAddresses = NULL;
    ULONG family = AF_UNSPEC;
    ULONG flags = GAA_FLAG_INCLUDE_PREFIX;

    int index = 0;
    int count;
    ULONG i;
    PIP_ADAPTER_ADDRESSES pCurrentAddress = NULL;
    PIP_ADAPTER_UNICAST_ADDRESS pUnicast = NULL;
    PIP_ADAPTER_ANYCAST_ADDRESS pAnycast = NULL;
    PIP_ADAPTER_MULTICAST_ADDRESS pMulticast = NULL;
    IP_ADAPTER_DNS_SERVER_ADDRESS *pDnsServer = NULL;
    IP_ADAPTER_PREFIX *pPrefix = NULL;

    _tsetlocale(LC_ALL, _T(""));

    if (argc != 1 && argc != 2)
    {
        _tprintf(_T("Usage:\n\tlist_network_interfaces [4|6]\n"));
        return EXIT_FAILURE;
    }

    if (argc == 2)
    {
        if (argv[1][0] == _T('4') && argv[1][1] == _T('\0'))
            family = AF_INET;
        else if (argv[1][0] == _T('6') && argv[1][1] == _T('\0'))
            family = AF_INET6;
    }

    pAddresses = GetAdaptersAddressesEx(family, flags);
    if (pAddresses == NULL)
    {
        _tprintf(_T("Failed to get a list of address of network adapters.\n"));
        return EXIT_FAILURE;
    }

    for (pCurrentAddress = pAddresses; pCurrentAddress != NULL; pCurrentAddress = pCurrentAddress->Next)
    {
        _tprintf(_T("#%d ---------------------\n"), ++index);

        _tprintf(_T("\tLength of the IP_ADAPTER_ADDRESS struct: %ld\n"), pCurrentAddress->Length);
        _tprintf(_T("\tIfIndex (IPv4 interface): %u\n"), pCurrentAddress->IfIndex);
        _tprintf(_T("\tAdapter name: %S\n"), pCurrentAddress->AdapterName);

        for (count = 0, pUnicast = pCurrentAddress->FirstUnicastAddress; pUnicast != NULL; pUnicast = pUnicast->Next)
            count += 1;
        if (count > 0)
            _tprintf(_T("\tNumber of Unicast Addresses: %d\n"), count);

        for (count = 0, pAnycast = pCurrentAddress->FirstAnycastAddress; pAnycast != NULL; pAnycast = pAnycast->Next)
            count += 1;
        if (count > 0)
            _tprintf(_T("\tNumber of Anycast Addresses: %d\n"), count);

        for (count = 0, pMulticast = pCurrentAddress->FirstMulticastAddress; pMulticast != NULL; pMulticast = pMulticast->Next)
            count += 1;
        if (count > 0)
            _tprintf(_T("\tNumber of Multicast Addresses: %d\n"), count);

        for (count = 0, pDnsServer = pCurrentAddress->FirstDnsServerAddress; pDnsServer != NULL; pDnsServer = pDnsServer->Next)
            count += 1;
        if (count > 0)
            _tprintf(_T("\tNumber of DnsServer Addresses: %d\n"), count);

        _tprintf(_T("\tDNS Suffix: %wS\n"), pCurrentAddress->DnsSuffix);
        _tprintf(_T("\tDescription: %wS\n"), pCurrentAddress->Description);
        _tprintf(_T("\tFriendly name: %wS\n"), pCurrentAddress->FriendlyName);

        if (pCurrentAddress->PhysicalAddressLength != 0)
        {
            _tprintf(_T("\tPhysical address: "));
            for (i = 0; i < pCurrentAddress->PhysicalAddressLength; i++)
            {
                if (i == pCurrentAddress->PhysicalAddressLength - 1)
                    _tprintf(_T("%.2X\n"), (int)pCurrentAddress->PhysicalAddress[i]);
                else
                    _tprintf(_T("%.2X-"), (int)pCurrentAddress->PhysicalAddress[i]);
            }
        }

        _tprintf(_T("\tFlags: %ld\n"), pCurrentAddress->Flags);
        _tprintf(_T("\tMtu: %lu\n"), pCurrentAddress->Mtu);
        _tprintf(_T("\tIfType: %ld\n"), pCurrentAddress->IfType);
        _tprintf(_T("\tOperStatus: %ld\n"), pCurrentAddress->OperStatus);
        _tprintf(_T("\tIpv6IfIndex (IPv6 interface): %u\n"), pCurrentAddress->Ipv6IfIndex);

        _tprintf(_T("\tZoneIndices (hex): "));
        for (i = 0; i < 16; i++)
            _tprintf(_T("%lx "), pCurrentAddress->ZoneIndices[i]);
        _tprintf(_T("\n"));

        _tprintf(_T("\tTransmit link speed: %I64u\n"), pCurrentAddress->TransmitLinkSpeed);
        _tprintf(_T("\tReceive link speed: %I64u\n"), pCurrentAddress->ReceiveLinkSpeed);

        for (count = 0, pPrefix = pCurrentAddress->FirstPrefix; pPrefix != NULL; pPrefix = pPrefix->Next)
            count += 1;
        if (count > 0)
            _tprintf(_T("\tNumber of IP Adapter Prefix entries: %d\n"), count);
    }

    FreeAdaptersAddresses(pAddresses);

    return 0;
}


// References:
// https://github.com/zeromq/libzmq/blob/v4.3.4/src/ip_resolver.cpp#L622-L700
// [How can I get to know the IP address for interfaces in C?](https://stackoverflow.com/questions/4139405/how-can-i-get-to-know-the-ip-address-for-interfaces-in-c)
// [is_wireless.c](https://gist.github.com/edufelipe/6108057)
// [Porting getifaddrs to Win XP](https://stackoverflow.com/questions/3069082/porting-getifaddrs-to-win-xp)
// [GetAdaptersAddresses function (iphlpapi.h)](https://docs.microsoft.com/en-us/windows/win32/api/iphlpapi/nf-iphlpapi-getadaptersaddresses)
// https://github.com/apple/cups/blob/master/cups/getifaddrs-internal.h
// https://github.com/apple/cups/blob/master/cups/getifaddrs.c
// https://github.com/steve-o/openpgm/blob/master/openpgm/pgm/getifaddrs.c
// [Alternative to gethostbyname](https://stackoverflow.com/questions/6638580/alternative-to-gethostbyname)
// http://beej.us/guide/bgnet/html/
// https://github.com/steve-o/openpgm/blob/master/openpgm/pgm/getifaddrs.c
// https://man7.org/linux/man-pages/man3/getifaddrs.3.html
// https://linux.die.net/man/3/getifaddrs
// [bind socket to network interface](https://stackoverflow.com/questions/14478167/bind-socket-to-network-interface)
// [How bind socket to device in windows?](https://stackoverflow.com/questions/1951578/how-bind-socket-to-device-in-windows)
// [Using a specific network interface for a socket in windows](https://stackoverflow.com/questions/2065495/using-a-specific-network-interface-for-a-socket-in-windows/2080495#2080495)
