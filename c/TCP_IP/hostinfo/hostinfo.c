// 2018-08-07T18:10+08:00
#include <errno.h>
#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../tcpip.h"


#ifndef OLD_SCHOOL_STYLE
#define OLD_SCHOOL_STYLE (0)
#endif


#if OLD_SCHOOL_STYLE
int main(int argc, char *argv[])
#else
int _tmain(int argc, _TCHAR *argv[])
#endif
{
#if OLD_SCHOOL_STYLE
    struct hostent *host;

    if (argc != 2)
    {
        fprintf(stdout, "Usage:\n  hostrans <host>\n");
        return EXIT_FAILURE;
    }

    TCP_IP_INIT();

    if (_istalpha(argv[1][0]))
    {
        host = gethostbyname(argv[1]);
    }
    else
    {
        struct in_addr addr;
        addr.s_addr = inet_addr(argv[1]);
        if (addr.s_addr != INADDR_NONE)
        {
            host = gethostbyaddr((const char *)&addr, 4, AF_INET);
        }
        else
        {
            fprintf(stderr, "Invalid IPv4 address.\n");
            return EXIT_FAILURE;
        }
    }
    
    if (host != NULL)
    {
        printf(
            "Official name: %s\n"
            "Alternate names: %s\n"
            "Address type: ",
            host->h_name,
            host->h_aliases[0]);

#define IN_CASE_OF(addrtype) \
        case addrtype: printf(#addrtype "\n"); break

        switch (host->h_addrtype)
        {
        IN_CASE_OF(AF_INET);
        IN_CASE_OF(AF_INET6);
#ifdef WIN32
        IN_CASE_OF(AF_NETBIOS);
#endif
        default: printf("%d\n", host->h_addrtype); break;
        }

#undef IN_CASE_OF

        printf("Address length: %d\n", host->h_length);
        {
            struct in_addr addr;
            int i = 0;
            while (1)
            {
                char *addr_ptr = host->h_addr_list[i++];
                if (addr_ptr == NULL)
                    break;

                addr.s_addr = *(u_long *)addr_ptr;
                printf("IP #%d: %s\n", i, inet_ntoa(addr));
            }
        }

        return EXIT_SUCCESS;
    }
    else
    {
#ifdef WIN32
        DWORD dwError = WSAGetLastError();

        switch (dwError)
        {
        case WSAHOST_NOT_FOUND:
            fprintf(stderr, "Host not found.\n");
            break;
        case WSANO_DATA:
            fprintf(stderr, "No data record found.\n");
            break;
        case 0:
            fprintf(stderr, "No error.\n");
            break;
        default:
            fprintf(stderr, "Unknown error.\n");
            break;
        }
#else
        fprintf(stderr, "hostinfo failed: %s.\n", gai_strerror(errno));
#endif

        return EXIT_FAILURE;
    }

#else
    int result;
    int i = 0;
    addrinfo_t hints;
    addrinfo_t *ailist = NULL;
    addrinfo_t *ptr;

#ifdef WIN32
    _tsetlocale(LC_COLLATE, _T(""));
#endif

    TCP_IP_INIT();

    if (argc != 2 && argc != 3)
    {
        fprintf(stdout,
            "Usage:\n"
            "  hostinfo <host>\n"
            "  hostinfo -s <serv>\n"
            "  hostinfo <host> <serv>\n");
        return EXIT_FAILURE;
    }

    if (argv[1][0] == _T('-'))
    {
        if (argv[1][1] != _T('s'))
        {
            _ftprintf(stderr, _T("Unknown option '%s'\n"), argv[1]);
            return EXIT_FAILURE;
        }
        else if (argc != 3)
        {
            fprintf(stderr, "<serv> required.\n");
            return EXIT_FAILURE;
        }
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    result = getaddrinfo(
        argv[1][0] == _T('-') ? NULL : argv[1],
        argc == 3 ? argv[2] : NULL,
        &hints,
        &ailist);
    if (result != 0)
    {
        _ftprintf(stderr, _T("getaddrinfo failed(%d): %s\n"), result, gai_strerror(result));
        return EXIT_FAILURE;
    }

    for (ptr = ailist; ptr != NULL; ptr = ptr->ai_next)
    {
        printf("#%d ---------------------\n", ++i);
        printf("  Flags: 0x%x\n", ptr->ai_flags);
        printf("  Family: ");

#define IN_CASE_OF(c) \
        case c: printf(#c "\n"); break

        switch (ptr->ai_family)
        {
        IN_CASE_OF(AF_UNSPEC);

        case AF_INET:
            printf("AF_INET\n");
            {
                struct sockaddr_in *sockaddr_ipv4 = (struct sockaddr_in *)ptr->ai_addr;
                _TCHAR ip[INET_ADDRSTRLEN];

                _TCHAR host[NI_MAXHOST];
                _TCHAR serv[NI_MAXSERV];

                printf("  Host: ");
                result = getnameinfo(ptr->ai_addr, ptr->ai_addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, 0);
                if (result == 0)
                    _tprintf(_T("%s:%s\n"), host, serv);
                else
#ifdef WIN32
                    fprintf(stderr, "  getnameinfo failed: %d\n", WSAGetLastError());
#else
                    fprintf(stderr, "  getnameinfo failed(%d): %s\n", errno, strerror(errno));
#endif

                if (inet_ntop(AF_INET, sockaddr_ipv4, ip, INET_ADDRSTRLEN) != NULL)
                    _tprintf(_T("  IPv4 address: %s\n"), ip);
                else
#ifdef WIN32
                    fprintf(stderr, "  inet_ntop failed: %d\n", WSAGetLastError());
#else
                    fprintf(stderr, "  inet_ntop failed(%d): %s\n", errno, strerror(errno));
#endif
            }
            break;
        case AF_INET6:
            printf("AF_INET6\n");
            {
                struct sockaddr_in6 *sockaddr_ipv6 = (struct sockaddr_in6 *)ptr->ai_addr;
                _TCHAR ip[INET6_ADDRSTRLEN];

                _TCHAR host[NI_MAXHOST];
                _TCHAR serv[NI_MAXSERV];

                printf("  Host: ");
                result = getnameinfo(ptr->ai_addr, ptr->ai_addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, 0);
                if (result == 0)
                    _tprintf(_T("%s:%s\n"), host, serv);
                else
#ifdef WIN32
                    fprintf(stderr, "  getnameinfo failed: %d\n", WSAGetLastError());
#else
                    fprintf(stderr, "  getnameinfo failed(%d): %s\n", errno, strerror(errno));
#endif

#ifdef WIN32
                DWORD dwAddressStringLength = INET6_ADDRSTRLEN;
                result = WSAAddressToString((LPSOCKADDR)sockaddr_ipv6, (DWORD)ptr->ai_addrlen, NULL, ip, &dwAddressStringLength);
                if (result != 0)
                    printf("  WSAAddressToString failed: %d\n", WSAGetLastError());
                else
                    _tprintf(_T("  IPv6 address: %s\n"), ip);
#else
                if (inet_ntop(AF_INET6, sockaddr_ipv6, ip, INET6_ADDRSTRLEN) != NULL)
                    _tprintf(_T("  IPv6 address: %s\n"), ip);
                else
                    fprintf(stderr, "  inet_ntop failed(%d): %s\n", errno, strerror(errno));
#endif
            }
            break;

#ifdef WIN32
        IN_CASE_OF(AF_NETBIOS);
#endif

        default:
            printf("Other(%d)\n", ptr->ai_family);
            break;
        }

        printf("  Socket type: ");
        switch (ptr->ai_socktype) {
        case 0:
            printf("Unspecified\n");
            break;

        IN_CASE_OF(SOCK_STREAM);
        IN_CASE_OF(SOCK_DGRAM);
        IN_CASE_OF(SOCK_RAW);
        IN_CASE_OF(SOCK_RDM);
        IN_CASE_OF(SOCK_SEQPACKET);

        default:
            printf("Other(%d)\n", ptr->ai_socktype);
            break;
        }

        printf("  Protocol: ");
        switch (ptr->ai_protocol) {
        case 0:
            printf("Unspecified\n");
            break;

        IN_CASE_OF(IPPROTO_TCP);
        IN_CASE_OF(IPPROTO_UDP);

        default:
            printf("Other(%d)\n", ptr->ai_protocol);
            break;
        }

        _tprintf(_T("  Length of this sockaddr: %u\n"), (unsigned)ptr->ai_addrlen);
        _tprintf(_T("  Canonical name: %s\n"), ptr->ai_canonname);
    }

    freeaddrinfo(ailist);
    return EXIT_SUCCESS;
#endif
}


// References:
// Beej's Guide to Network Programming Using Internet Sockets
// https://docs.microsoft.com/zh-cn/windows/desktop/api/ws2tcpip/nf-ws2tcpip-getaddrinfo
// https://docs.microsoft.com/en-us/windows/desktop/api/winsock2/nf-winsock2-wsaaddresstostringa
// https://en.wikipedia.org/wiki/Getaddrinfo
// https://tools.ietf.org/html/rfc3493
// https://stackoverflow.com/questions/5956516/getaddrinfo-and-ipv6
