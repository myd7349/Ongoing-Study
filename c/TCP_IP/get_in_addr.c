#include <assert.h>

#include "get_in_addr.h"


// get sockaddr, IPv4 or IPv6
void *get_in_addr(struct sockaddr *sa)
{
    assert(sa != NULL);
    assert(sa->sa_family == AF_INET || sa->sa_family == AF_INET6);

    if (sa->sa_family == AF_INET)
        return &(((struct sockaddr_in *)sa)->sin_addr);
    else
        return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}


// References:
// Beej's Guide to Network Programming Using Internet Sockets, Ch6.1
