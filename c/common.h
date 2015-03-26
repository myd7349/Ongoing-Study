/* 2015-03-02T11:36+08:00 */
#ifndef COMMON_H_
#define COMMON_H_

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

/* To be continued... */

#endif /* COMMON_H_ */