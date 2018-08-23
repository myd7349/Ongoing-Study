#include "sendall.h"

#include <assert.h>


int sendall(socket_t sock, char *buf, int len)
{
    int bytes_sent = 0;
    int res;

    assert(sock != INVALID_SOCKET);
    assert(buf != NULL);
    assert(len > 0);

    while (len > 0)
    {
        res = send(sock, buf + bytes_sent, len, 0);
        if (res == SOCKET_ERROR)
            break;

        bytes_sent += res;
        len -= res;
    }

    return bytes_sent;
}
