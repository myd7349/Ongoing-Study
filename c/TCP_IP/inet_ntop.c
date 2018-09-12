#include "inet_ntop.h"

#if defined(__linux__)
# include <errno.h>
#endif

#include <string.h>


// Shameless stolen from [0] with some modification so that nobody will find out.
const _TCHAR *inet_ntop_c(int af, const void *src, _TCHAR *dst, socklen_t size)
{
    int result;

    if (af != AF_INET && af != AF_INET6)
    {
#if defined(_WIN32)
        WSASetLastError(WSAEAFNOSUPPORT);
#elif defined(__linux__)
        errno = EAFNOSUPPORT;
#else
# error Unsupported platform!
#endif

        return NULL;
    }

    if (dst == NULL || size == 0)
    {
#if defined(_WIN32)
        WSASetLastError(WSA_INVALID_PARAMETER);
#elif defined(__linux__)
        errno = ENOSPC;
#else
# error Unsupported platform!
#endif

        return NULL;
    }

    if (af == AF_INET)
    {
        struct sockaddr_in addr_in = { AF_INET };
        memcpy(&addr_in.sin_addr, src, sizeof(struct in_addr));

        result = getnameinfo((const struct sockaddr *)&addr_in,
            sizeof(struct sockaddr_in), dst, size, NULL, 0, NI_NUMERICHOST);
        if (result != 0)
            return NULL;
        
        return dst;
    }
    else
    {
        struct sockaddr_in6 addr_in6 = { AF_INET6 };
        memcpy(&addr_in6.sin6_addr, src, sizeof(struct in_addr6));

        result = getnameinfo((const struct sockaddr *)&addr_in6,
            sizeof(struct sockaddr_in6), dst, size, NULL, 0, NI_NUMERICHOST);
        if (result != 0)
            return NULL;

        return dst;
    }
}


// References:
// [0] https://www.codeproject.com/articles/2477/multi-threaded-client-server-socket-class
// [1] Beej's Guide to Network Programming Using Internet Sockets, 9.14
// [2] http://man7.org/linux/man-pages/man3/inet_ntop.3.html
// [3] https://docs.microsoft.com/en-us/windows/desktop/api/wsipv6ok/nf-wsipv6ok-inet_addr
