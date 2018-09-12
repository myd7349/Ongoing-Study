#ifndef GET_IN_ADDR_H_
#define GET_IN_ADDR_H_

#include "../common.h"
#include "tcpip.h"

C_API_BEGIN

void *get_in_addr(struct sockaddr *sa);

C_API_END

#endif // GET_IN_ADDR_H_
