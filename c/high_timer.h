#ifndef HIGH_RESOLUTION_TIMER_H_
#define HIGH_RESOLUTION_TIMER_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __linux__
#include <sys/time.h>
#endif

#include "common.h"


C_API_BEGIN

typedef struct high_timer_impl_t
{
#if defined(_WIN32)
    int64_t start_time;
#elif defined(__linux__)
    struct timeval start_time;
#else
#error high_timer: Unsupported platform!
#endif
    bool    started;
} high_timer_t;

void high_timer_start(high_timer_t *timer);
int64_t high_timer_ellapsed_ms(high_timer_t *timer);

C_API_END

#endif // HIGH_RESOLUTION_TIMER_H_
