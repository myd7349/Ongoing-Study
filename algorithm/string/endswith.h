#ifndef ENDS_WITH_H_
#define ENDS_WITH_H_

#include <stdbool.h>
#include <stddef.h>

#include "../../c/common.h"
#include "../../c/tchardef.h"


C_API_BEGIN

bool endswith(const _TCHAR *s, const _TCHAR *s2);
bool endswithi(const _TCHAR *s, const _TCHAR *s2);

bool endswithex(const _TCHAR *s, const _TCHAR *s2, size_t count);
bool endswithiex(const _TCHAR *s, const _TCHAR *s2, size_t count);

C_API_END

#endif // ENDS_WITH_H_
