#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../tcpip.h"


int _tmain()
{
    int result;
    char hostname[HOST_NAME_MAX];

    TCP_IP_INIT();

    result = gethostname(hostname, HOST_NAME_MAX);
    if (result == 0)
    {
        printf("%s", hostname);
        return EXIT_SUCCESS;
    }
    else
    {
        fprintf(stderr, "gethostname returned %d: %s\n", result, strerror(errno));
        return EXIT_FAILURE;
    }
}
