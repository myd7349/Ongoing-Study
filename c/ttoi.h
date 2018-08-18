#ifndef TTOI_H_
#define TTOI_H_

#include <stdbool.h>

#include "common.h"
#include "tchardef.h"

C_API_BEGIN

long ttol(const _TCHAR *s, bool *ok);
int ttoi(const _TCHAR *s, bool *ok);

C_API_END

#endif // TTOI_H_
