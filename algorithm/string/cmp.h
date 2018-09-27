#ifndef STRCMP_H_
#define STRCMP_H_

#include <stddef.h>

#include "../../c/common.h"
#include "../../c/tchardef.h"

C_API_BEGIN

int cmp(const _TCHAR *s1, const _TCHAR *s2);
int ncmp(const _TCHAR *s1, const _TCHAR *s2, size_t count);

int icmp(const _TCHAR *s1, const _TCHAR *s2);
int nicmp(const _TCHAR *s1, const _TCHAR *s2, size_t count);

C_API_END

#endif // STRCMP_H_
