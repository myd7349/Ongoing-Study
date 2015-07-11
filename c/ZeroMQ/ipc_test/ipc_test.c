// 2015-05-16T16:53+08:00
// Test if IPC works on windows.
#include "czmq.h"

#ifndef TEST_IPC
# define TEST_IPC (1)
#endif

int main(void)
{
	zctx_t *ctx = zctx_new();

	void *req = zsocket_new(ctx, ZMQ_REQ);
	void *rep = zsocket_new(ctx, ZMQ_REP);

	int port;
#if TEST_IPC
	port = zsocket_bind(req, "ipc://reqvsrep.ipc");
	printf("%d\n", port);
	port = zsocket_connect(rep, "ipc://reqvsrep.ipc");
	printf("%d\n", port);
#else
	port = zsocket_bind(req, "tcp://*:5678");
	printf("%d\n", port);
	port = zsocket_connect(rep, "tcp://localhost:5678");
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

	zctx_destroy(&ctx);

	system("pause");
	return 0;
}
// References:
// [Does zeromq support IPC as a transport channel on windows?](http://stackoverflow.com/questions/15386121/does-zeromq-support-ipc-as-a-transport-channel-on-windows)
// [IPC not supported on windows](https://zeromq.jira.com/browse/LIBZMQ-153)