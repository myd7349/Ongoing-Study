/* 2015-03-02T11:36+08:00 */
#ifndef COMMON_H_
#define COMMON_H_

#ifdef _MSC_VER
# define _CRT_SECURE_NO_WARNINGS
# define _CRT_NONSTDC_NO_DEPRECATE

# pragma warning(disable: 4005)
#endif

#include <assert.h>
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

/* STR */
/*
TODO:
typedef enum {
    CRC_32 = 32
} crc_type_t;

#define CRC_HEX_CHARS(crc_type) ((crc_type) / 4 + 1)
#define CRC32_HEX_CHARS CRC_HEX_CHARS(CRC_32)
printf("%s\n", STR(CRC32_HEX_CHARS));

*/
#define STR_IMPL(c) #c
#define STR(c) STR_IMPL(c)

/* CONCAT */
#define CONCAT_IMPL(c1, c2) c1 ## c2
#define CONCAT(c1, c2) CONCAT_IMPL(c1, c2)

/* RANDOF */
/* Generate a random number from [0...num-1] */
#define RANDOF(num) ((int)((float)(num) * rand() / (RAND_MAX + 1.0)))

/* RANDINT */
#define RANDINT(lo, hi) (RANDOF((hi) - (lo)) + (lo))

/* C_API_* */
#ifdef __cplusplus
# define C_API_BEGIN extern "C" {
# define C_API_END   }
#else
# define C_API_BEGIN
# define C_API_END
#endif


/* To be continued... */

#endif /* COMMON_H_ */
