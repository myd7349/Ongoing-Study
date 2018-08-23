#ifndef SEND_ALL_H_
#define SEND_ALL_H_

#include "../common.h"
#include "tcpip.h"


C_API_BEGIN

int sendall(socket_t sock, char *buf, int len);

C_API_END

#endif // SEND_ALL_H_
