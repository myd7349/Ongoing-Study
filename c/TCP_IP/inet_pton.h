#ifndef INET_PTON_H_
#define INET_PTON_H_

#include "../common.h"
#include "../tchardef.h"


C_API_BEGIN

int inet_pton_c(int af, const _TCHAR *src, void *dst);

C_API_END

#endif // INET_PTON_H_

