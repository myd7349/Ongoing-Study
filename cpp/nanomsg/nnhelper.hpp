// 2016-08-23T20:01+08:00
// By myd7349
#ifndef NNHELPER_H_
#define NNHELPER_H_

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include <nanomsg/nn.h>


#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# include <Windows.h>
#elif defined(__linux__)
# include <time.h>
#else
# error Not tested yet!
#endif


inline int nnh_sendstr(int sock, const char *str)
{
    assert(sock >= 0);
    assert(str != NULL);

    int len = std::strlen(str);
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
    char *str = (char *)std::malloc(nbytes + 1);
    if (str != NULL)
        std::strncpy(str, (const char *)buf, nbytes);
    str[nbytes] = '\0';

    nn_freemsg(buf);

    return str;
}


void nnh_fatal_error(const char *func_name)
{
    std::fprintf(stderr, "%s(%d): %s: %s\n", __FILE__, __LINE__, func_name, nn_strerror(nn_errno()));
    std::exit(EXIT_FAILURE);
}


inline std::string nnh_recv_string(int sock)
{
    char *s = nnh_recvstr(sock);
    if (s == NULL)
        nnh_fatal_error("nn_recv");
    std::string str = s;
    std::free(s);
    return str;
}


// See zguide:zhelpers.h
inline void nnh_sleep(int msecs)
{
#ifdef _WIN32
    Sleep(msecs);
#elif defined(__linux__)
    struct timespec t;
    t.tv_sec = msecs / 1000;
    t.tv_nsec = (msecs % 1000) * 1000000;
    nanosleep(&t, NULL);
#else
# error Not tested yet!
#endif
}

#endif // NNHELPER_H_
