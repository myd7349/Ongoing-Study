// 2017-09-04T09:30+08:00
// Test if IPC works on windows.
#include "czmq.h"


#ifndef TEST_IPC
# define TEST_IPC (1)
#endif


#ifndef TEST_INPROC
# define TEST_INPROC (0)
#endif


int main(void)
{
    zsock_t *req = zsock_new(ZMQ_REQ);
    zsock_t *rep = zsock_new(ZMQ_REP);

    int port;
#if TEST_IPC
    port = zsock_bind(req, "ipc://reqvsrep.ipc");
    printf("%d\n", port);
    port = zsock_connect(rep, "ipc://reqvsrep.ipc");
    printf("%d\n", port);
#elif TEST_INPROC
    port = zsock_bind(req, "inproc://backend");
    printf("%d\n", port);
    port = zsock_connect(rep, "inproc://backend");
    printf("%d\n", port);
#else
    port = zsock_bind(req, "tcp://*:5678");
    printf("%d\n", port);
    port = zsock_connect(rep, "tcp://localhost:5678");
    printf("%d\n", port);
#endif

    zstr_send(req, "Hello");
    
    char *request = zstr_recv(rep);
    if (request != NULL) {
        printf("%s\n", request);
        free(request);
    }

    zstr_send(rep, "World");

    char *reply = zstr_recv(req);
    if (reply != NULL) {
        printf("%s\n", reply);
        free(reply);
    }

    zsock_destroy(&req);
    zsock_destroy(&rep);

#if defined __WINDOWS__
    zsys_shutdown();
#endif

    return 0;
}

// References:
// [Does zeromq support IPC as a transport channel on windows?](http://stackoverflow.com/questions/15386121/does-zeromq-support-ipc-as-a-transport-channel-on-windows)
// [IPC not supported on windows](https://zeromq.jira.com/browse/LIBZMQ-153)
