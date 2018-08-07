#ifndef TCP_IP_H_
#define TCP_IP_H_

#ifdef WIN32

#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

#include <stdio.h>
#include <stdlib.h>

#include <tchar.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#ifdef _MSC_VER
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable: 4996)
#endif

#define HOST_NAME_MAX _MAX_PATH

#define TCP_IP_INIT() \
{ \
    WSADATA wsaData; \
    int wsadata_result = WSAStartup(MAKEWORD(2, 2), &wsaData); \
    if (wsadata_result != 0) \
    { \
        fprintf(stderr, "WSAStartup failed: %d\n", wsadata_result); \
        return EXIT_FAILURE; \
    } \
    \
    atexit((void(*)(void))WSACleanup); \
}

typedef ADDRINFOT addrinfo_t;

#define getnameinfo GetNameInfo
#define getaddrinfo GetAddrInfo
#define freeaddrinfo FreeAddrInfo
#define inet_ntop InetNtop
#define inet_pton InetPton

#else

#include <arpa/inet.h>
#include <limits.h> // HOST_NAME_MAX
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h> // gethostname
#include <sys/types.h>
#include <sys/socket.h>

#define _tmain main
#define _TCHAR char
#define _T(x) x
#define _istalpha isalpha
#define _tprintf printf
#define _ftprintf fprintf

#define TCP_IP_INIT() ((void)0)

typedef struct addrinfo addrinfo_t;

#endif

#endif // TCP_IP_H_


// References:
// man: gethostname
// https://stackoverflow.com/questions/30084116/host-name-max-undefined-after-include-limits-h

