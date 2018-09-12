#ifndef INET_NTOP_H_
#define INET_NTOP_H_

#include "../common.h"
#include "tcpip.h"


C_API_BEGIN

const _TCHAR *inet_ntop_c(int af, const void *src, _TCHAR *dst, socklen_t size);

C_API_END

#endif // INET_NTOP_H_
