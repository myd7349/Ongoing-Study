#ifndef TCP_IP_H_
#define TCP_IP_H_

#include "../tchardef.h"

#if defined(_WIN32) || \
    defined(__MINGW32__) || \
    defined(__MINGW64__)

#include <stdio.h>
#include <stdlib.h>

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h> // GetAdaptersAddresses

#ifdef _MSC_VER
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "IPHLPAPI.lib")
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
typedef SOCKET socket_t;

#define getnameinfo GetNameInfo
#define getaddrinfo GetAddrInfo
#define freeaddrinfo FreeAddrInfo

#if defined(_MSC_VER)
# define inet_ntop InetNtop
# define inet_pton InetPton
#endif

#define closesock closesocket

#define print_error(func_name, error) \
    _ftprintf(stderr, func_name _T(" failed(%d): %s\n"), (error), gai_strerror((error)))
#define print_error_ex(func_name) print_error(func_name, WSAGetLastError())

#else

#include <arpa/inet.h>
#include <errno.h>
#include <limits.h> // HOST_NAME_MAX
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h> // gethostname
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>


#define TCP_IP_INIT() ((void)0)

typedef struct addrinfo addrinfo_t;
typedef int socket_t;

#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)

#define closesock close

#define print_error(func_name, error) \
    _ftprintf(stderr, \
        func_name \
        _T(" failed(%d):\n") \
        _T("  strerror: %s\n") \
        _T("  gai_strerror: %s\n"), \
        (error), strerror(error), gai_strerror((error)))
#define print_error_ex(func_name) print_error(func_name, errno)

#endif

#endif // TCP_IP_H_


// References:
// man: gethostname
// https://stackoverflow.com/questions/30084116/host-name-max-undefined-after-include-limits-h
// https://github.com/boostorg/predef/blob/develop/include/boost/predef/platform/mingw.h
// https://github.com/Genymobile/scrcpy/blob/master/app/src/util/net.h
