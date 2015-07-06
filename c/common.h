/* 2015-03-02T11:36+08:00 */
#ifndef COMMON_H_
#define COMMON_H_

#ifdef _MSC_VER
# define _CRT_SECURE_NO_WARNINGS
# define _CRT_NONSTDC_NO_DEPRECATE

# pragma warning(disable: 4005)
#endif

#include <stdlib.h>

/* FREE */
/* http://www.zhihu.com/question/24943388 */
#define FREE(ptr) do { free(ptr); ptr = NULL; } while (0)

/* PAUSE */
#ifdef _MSC_VER
# ifdef NDEBUG
#  define PAUSE() (__noop)
# else
#  define PAUSE() system("pause")
# endif
#else
# define PAUSE() ((void)0)
#endif

/* ARRAYSIZE */
#define ARRAYSIZE(arr) (sizeof(arr) / sizeof(arr[0]))

/* To be continued... */

#endif /* COMMON_H_ */
