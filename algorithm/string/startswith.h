#ifndef STARTS_WITH_H_
#define STARTS_WITH_H_

#include <stdbool.h>
#include <stddef.h>

#include "../../c/common.h"
#include "../../c/tchardef.h"


C_API_BEGIN

bool startswith(const _TCHAR *s, const _TCHAR *s2);
bool startswithi(const _TCHAR *s, const _TCHAR *s2);

bool startswithex(const _TCHAR *s, const _TCHAR *s2, size_t count);
bool startswithiex(const _TCHAR *s, const _TCHAR *s2, size_t count);

C_API_END

#endif // STARTS_WITH_H_
