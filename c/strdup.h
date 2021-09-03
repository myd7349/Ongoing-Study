#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(HAVE__STRDUP)
# include <string.h> // _strdup
# undef strdup
# define strdup _strdup
#elif defined(HAVE_STRDUP)
# include <string.h> // strdup
#else
char *strdup(const char *str);
#endif

#ifdef __cplusplus
}
#endif


// Example:
// curl/pctutil
