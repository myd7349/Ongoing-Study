#pragma once

#include <cassert>
#include <cstddef> // std::size_t

/* PLATFORM_API */
#ifndef PLATFORM_API
#if defined(_WIN32) || defined(__MINGW32__) || defined(__MINGW64__) || \
    defined(__CYGWIN__)
#define PLATFORM_IMPORT __declspec(dllimport)
#define PLATFORM_EXPORT __declspec(dllexport)
#define PLATFORM_LOCAL
#else
#if __GNUC__ >= 4
#define PLATFORM_IMPORT __attribute__((visibility("default")))
#define PLATFORM_EXPORT __attribute__((visibility("default")))
#define PLATFORM_LOCAL __attribute__((visibility("hidden")))
#else
#define PLATFORM_IMPORT
#define PLATFORM_EXPORT
#define PLATFORM_LOCAL
#endif
#endif
#endif


#if defined(_WIN32) || defined(__MINGW32__) || defined(__MINGW64__) || \
    defined(__CYGWIN__)

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <WinSock2.h>
#include <WS2tcpip.h>

#ifdef _MSC_VER
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "IPHLPAPI.lib")
#endif

#define TCP_IP_INIT()                                                    \
{                                                                        \
    WSADATA wsaData;                                                     \
    int wsadata_result = WSAStartup(MAKEWORD(2, 2), &wsaData);           \
    if (wsadata_result != 0)                                             \
    {                                                                    \
        std::fprintf(stderr, "WSAStartup failed: %d\n", wsadata_result); \
        return EXIT_FAILURE;                                             \
    }                                                                    \
                                                                         \
    std::atexit((void (*)(void))WSACleanup);                             \
}

typedef SOCKET socket_t;
typedef unsigned long in_addr_t; // TODO: Test it with a 64-bit compiler.
typedef int socklen_t;

#define bzero(s, n) std::memset((s), 0, (n))

#ifndef PLATFORM_NO_DEPRECATED_APIS

// MSVC:
// warning C4996: 'inet_ntoa': Use inet_ntop() or InetNtop() instead or
// define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings.
// linux:
// https://linux.die.net/man/3/inet_ntoa
// The inet_ntoa() function converts the Internet host address in, given in
// network byte order, to a string in IPv4 dotted-decimal notation. The string
// is returned in a statically allocated buffer, which subsequent calls will overwrite. 
char *inet_ntoa_(struct in_addr in);

#define inet_ntoa inet_ntoa_

#endif

#else

#include <arpa/inet.h> // htons
#include <netdb.h>
#include <netinet/in.h>
#include <strings.h> // bzero
#include <sys/select.h> // select
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // close

#define TCP_IP_INIT() ((void)0)

typedef int socket_t;

#define INVALID_SOCKET (-1)
#define SOCKET_ERROR   (-1)
#define INFINITE       (0xFFFFFFFF)
#define ARRAYSIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define closesocket close

#endif

#ifndef PLATFORM_NO_DEPRECATED_APIS

// MSVC:
// warning C4996 : 'inet_addr' : Use inet_pton() or InetPton() instead or
// define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings.
// Linux:
// https://linux.die.net/man/3/inet_addr
// Avoid its use in favor of inet_aton(), inet_pton(3), or getaddrinfo(3) which
// provide a cleaner way to indicate error return.
inline in_addr_t inet_addr_(const char* cp)
{
    struct in_addr addr;
    int result = inet_pton(AF_INET, cp, &addr);
    if (result == 1)
    {
        return addr.s_addr;
    }
    else
    {
        assert(result == 0 || result == -1);
        return INADDR_NONE;
    }
}

#define inet_addr inet_addr_

#endif


// References:
// https://linux.die.net/man/3/inet_addr
// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-inet_addr
// https://docs.microsoft.com/en-us/windows/win32/api/ws2tcpip/nf-ws2tcpip-inet_pton
// https://linux.die.net/man/3/inet_ntoa
// https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-inet_ntoa
// https://docs.microsoft.com/en-us/windows/win32/api/ws2tcpip/nf-ws2tcpip-inet_ntop
// https://linux.die.net/man/3/inet_ntop
// https://linux.die.net/man/3/gai_strerror
