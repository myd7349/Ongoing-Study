// 2016-08-23T20:01+08:00
// By myd7349
#ifndef NNHELPER_H_
#define NNHELPER_H_

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <nanomsg/nn.h>


inline int nnh_sendstr(int sock, const char *str)
{
    assert(sock >= 0);
    assert(str != NULL);

    int len = strlen(str);
    int nbytes = nn_send(sock, str, len, 0);
    assert(nbytes == len);

    return nbytes;
}

inline char *nnh_recvstr(int sock)
{
    assert(sock >= 0);
    void *buf = NULL;
    int nbytes = nn_recv(sock, &buf, NN_MSG, 0);

    if (nbytes < 0)
        return NULL;

    //char *str = (char *)calloc(1, nbytes + 1);
    char *str = (char *)malloc(nbytes + 1);
    if (str != NULL)
        strncpy(str, (const char *)buf, nbytes);
    str[nbytes] = '\0';

    nn_freemsg(buf);

    return str;
}

#endif // NNHELPER_H_
