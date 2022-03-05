#include "Platform.h"


#if defined(_WIN32) || defined(__MINGW32__) || defined(__MINGW64__) || \
    defined(__CYGWIN__)

#ifndef PLATFORM_NO_DEPRECATED_APIS

char *inet_ntoa_(struct in_addr in)
{
    static char buffer[INET_ADDRSTRLEN];

    if (inet_ntop(AF_INET, &in, buffer, sizeof(buffer)) != NULL)
        return buffer;
    return NULL;
}

#endif

#endif


// References:
// https://github.com/microsoft/Windows-classic-samples/tree/main/Samples/Win7Samples/netds/winsock/inet_xtoy
