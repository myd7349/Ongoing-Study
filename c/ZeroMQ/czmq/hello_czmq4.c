// 2017-09-01T08:45+08:00
#include "czmq.h"


int main(void)
{
    zsock_t *sock = zsock_new(ZMQ_REQ);
    zsock_destroy(&sock);

#if defined(__WINDOWS__)
    zsys_shutdown();
#endif

    return 0;
}

// References:
// [Assertion failed: Successful WSASTARTUP not yet performed](https://github.com/zeromq/czmq/issues/1751)
