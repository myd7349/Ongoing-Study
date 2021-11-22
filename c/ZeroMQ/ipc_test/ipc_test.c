// 2017-09-04T09:30+08:00
// Note:
// This version does work with czmq 4.x. If you are using czmq 4.x, please
// refer https://github.com/myd7349/Ongoing-Study/blob/master/c/ZeroMQ/czmq/ipc_test.c


// 2015-05-16T16:53+08:00
// Test if IPC works on windows.
#include "zhelpers.h"


int main(void)
{
	void *ctx = zmq_ctx_new();

	void *req = zmq_socket(ctx, ZMQ_REQ);
	void *rep = zmq_socket(ctx, ZMQ_REP);

    char *request;
    char *reply;

	int rc;
#ifdef TEST_IPC
	rc = zmq_bind(req, "ipc://reqvsrep.ipc");
    assert(rc == 0);
	rc = zmq_connect(rep, "ipc://reqvsrep.ipc");
    assert(rc == 0);
#else
	rc = zmq_bind(req, "tcp://*:5678");
    assert(rc == 0);
	rc = zmq_connect(rep, "tcp://localhost:5678");
    assert(rc == 0);
#endif

    s_send(req, "Hello");
	
	request = s_recv(rep);
	if (request != NULL) {
		printf("%s\n", request);
		free(request);
	}

	s_send(rep, "World");

	reply = s_recv(req);
	if (reply != NULL) {
		printf("%s\n", reply);
		free(reply);
	}

    zmq_close(req);
    zmq_close(rep);
	zmq_ctx_destroy(ctx);

	return 0;
}


// References:
// [Does zeromq support IPC as a transport channel on windows?](http://stackoverflow.com/questions/15386121/does-zeromq-support-ipc-as-a-transport-channel-on-windows)
// [IPC not supported on windows](https://zeromq.jira.com/browse/LIBZMQ-153)
// https://github.com/zeromq/libzmq/pull/3717
