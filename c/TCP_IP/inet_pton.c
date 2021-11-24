#include "inet_pton.h"

#include <string.h>

#if defined(__linux__)
# include <errno.h>
#endif

#include "../bzero.h"
#include "get_in_addr.h"


// Shameless stolen from [0] with bug fixes.
int inet_pton_c(int af, const _TCHAR *src, void *dst)
{
    int result;
    addrinfo_t hints;
    addrinfo_t *ailist = NULL;

    if (af != AF_INET && af != AF_INET6)
    {
#if defined(_WIN32)
        WSASetLastError(WSAEAFNOSUPPORT);
#elif defined(__linux__)
        errno = EAFNOSUPPORT;
#else
# error Unsupported platform!
#endif

        return -1;
    }

#if defined(_WIN32)
    if (src == NULL || dst == NULL)
    {
        WSASetLastError(WSAEFAULT);
        return -1;
    }
#endif

    bzero(&hints, sizeof(hints));
    hints.ai_family = af;

    result = getaddrinfo(src, NULL, &hints, &ailist);
    if (result != SOCKET_ERROR && ailist != NULL)
    {
        memcpy(dst, get_in_addr(ailist->ai_addr), ailist->ai_addrlen);
        freeaddrinfo(ailist);
        return 1;
    }

    return 0;
}


// References:
// [0] https://www.codeproject.com/articles/2477/multi-threaded-client-server-socket-class
// [1] Beej's Guide to Network Programming Using Internet Sockets, 9.14
// [2] http://man7.org/linux/man-pages/man3/inet_pton.3.html
// [3] https://docs.microsoft.com/en-us/windows/desktop/api/ws2tcpip/nf-ws2tcpip-inet_pton
// [4] https://stackoverflow.com/questions/15370033/how-to-use-inet-pton-with-the-mingw-compiler
// https://github.com/curl/curl/blob/master/lib/inet_pton.c
