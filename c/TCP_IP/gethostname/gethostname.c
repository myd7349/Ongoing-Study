#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../tcpip.h"


size_t get_host_name_max()
{
#if defined(HOST_NAME_MAX)
    return HOST_NAME_MAX;
#endif

#if defined(_SC_HOST_NAME_MAX)
    long res = sysconf(_SC_HOST_NAME_MAX);
    if (res != -1)
        return res;
#endif

    // _POSIX_HOST_NAME_MAX
    return 255;
}


int _tmain()
{
    int result;
    size_t hostname_size = get_host_name_max();
    char *hostname = malloc(hostname_size);

    TCP_IP_INIT();

    result = gethostname(hostname, hostname_size);
    if (result == 0)
    {
        printf("%s\n", hostname);
        free(hostname);
        return EXIT_SUCCESS;
    }
    else
    {
        fprintf(stderr, "gethostname returned %d: %s\n", result, strerror(errno));
        free(hostname);
        return EXIT_FAILURE;
    }
}


// References:
// [Fix compilation on systems that do not define HOST_NAME_MAX](https://github.com/PowerDNS/pdns/pull/9127)
