#include "high_timer.h"

#include <assert.h>

#if defined(_WIN32)

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void high_timer_start(high_timer_t *timer)
{
    LARGE_INTEGER start;

    assert(timer != NULL);

    if (QueryPerformanceCounter(&start))
    {
        timer->start_time = start.QuadPart;
        timer->started = true;
    }
    else
    {
        timer->start_time = 0;
        timer->started = false;
    }
}


int64_t high_timer_elapsed_ms(high_timer_t *timer)
{
    return high_timer_elapsed_ns(timer) / 1000 / 1000;
}


int64_t high_timer_elapsed_us(high_timer_t *timer)
{
    return high_timer_elapsed_ns(timer) / 1000;
}


int64_t high_timer_elapsed_ns(high_timer_t *timer)
{
    LARGE_INTEGER stop;
    LARGE_INTEGER frequency;

    assert(timer != NULL);
    assert(timer->started);

    if (timer->started)
    {
        if (QueryPerformanceCounter(&stop) && QueryPerformanceFrequency(&frequency))
            return (int64_t)((stop.QuadPart - timer->start_time) * 1.0e9 / frequency.QuadPart);
        else
            return 0;
    }
    else
    {
        return 0;
    }
}

#elif defined(__linux__)

#ifdef HAVE_CLOCK_GETTIME

void high_timer_start(high_timer_t *timer)
{
    assert(timer != NULL);

    clock_gettime(CLOCK_REALTIME, &timer->start_time);
    timer->started = true;
}


int64_t high_timer_elapsed_ms(high_timer_t *timer)
{
    return high_timer_elapsed_ns(timer) / 1000 / 1000;
}


int64_t high_timer_elapsed_us(high_timer_t *timer)
{
    return high_timer_elapsed_ns(timer) / 1000;
}


int64_t high_timer_elapsed_ns(high_timer_t *timer)
{
    struct timespec current_spec;

    assert(timer != NULL);
    assert(timer->started);

    if (timer->started)
    {
        clock_gettime(CLOCK_REALTIME, &current_spec);
        return (int64_t)((current_spec.tv_sec - timer->start_time.tv_sec) * 1.0e9
            + (current_spec.tv_nsec - timer->start_time.tv_nsec));
    }
    else
    {
        return 0;
    }
}

#else

void high_timer_start(high_timer_t *timer)
{
    assert(timer != NULL);

    gettimeofday(&timer->start_time, NULL);
    timer->started = true;
}

int64_t high_timer_elapsed_ms(high_timer_t *timer)
{
    return high_timer_elapsed_us(timer) / 1000;
}


int64_t high_timer_elapsed_us(high_timer_t *timer)
{
    struct timeval stop;

    assert(timer != NULL);
    assert(timer->started);

    if (timer->started)
    {
        gettimeofday(&stop, NULL);
        return (int64_t)((stop.tv_sec - timer->start_time.tv_sec) * 1000.0 * 1000.0
            + (stop.tv_usec - timer->start_time.tv_usec));
    }
    else
    {
        return 0;
    }
}


int64_t high_timer_elapsed_ns(high_timer_t *timer)
{
    return high_timer_elapsed_us(timer) * 1000;
}

#endif

#else

#error high_timer: Unsupported platform!

#endif


// References:
// https://stackoverflow.com/questions/11354905/what-is-the-resolution-of-windows-high-performance-counter
// https://github.com/mloskot/spatial_index_benchmark/blob/master/high_resolution_timer.hpp
// https://github.com/miloyip/nativejson-benchmark/blob/master/src/timer.h
// https://stackoverflow.com/questions/21557816/whats-the-c-suffix-for-long-double-literals
// https://github.com/google/glog/blob/ba8a9f6952d04d1403b97df24e6836227751454e/src/utilities.cc#L194-L216
// https://stackoverflow.com/questions/3756323/how-to-get-the-current-time-in-milliseconds-from-c-in-linux
// https://linux.die.net/man/2/clock_gettime
// https://github.com/caryll/otfcc/blob/master/src/stopwatch.c
// https://github.com/microsoft/mimalloc/pull/23/files
// https://github.com/lemire/simdjson/blob/master/benchmark/benchmark.h
// https://github.com/mattreecebentley/plf_nanotimer/blob/master/plf_nanotimer.h
// https://github.com/ibireme/yybench/blob/master/src/yybench_time.h
// https://github.com/powturbo/TurboBench/blob/master/time_.h
// https://github.com/floooh/sokol/blob/master/sokol_time.h
// https://github.com/google/glog/commit/a1374c42009b8c37e774038b6d2a837c94d430e2
// https://github.com/google/glog/pull/669
// [rdtsc](https://github.com/zeromq/libzmq/issues/3366)
// https://github.com/chenshuo/muduo/blob/master/muduo/base/Timestamp.cc
// https://github.com/jingweizhanghuai/Morn/blob/e8d48c9dc54be71ae2e3b11de0851bbd601f21e2/include/morn_util.h#L303-L304
// [cputime](https://github.com/k0dai/cputime)
// https://github.com/libsdl-org/SDL/blob/main/src/timer/windows/SDL_systimer.c
// [Windows Timer Resolution: The Great Rule Change](https://randomascii.wordpress.com/2020/10/04/windows-timer-resolution-the-great-rule-change/)
// https://github.com/mattip/c_from_python/blob/master/main.c
// [Measure time in Linux - time vs clock vs getrusage vs clock_gettime vs gettimeofday vs timespec_get?](https://stackoverflow.com/questions/12392278/measure-time-in-linux-time-vs-clock-vs-getrusage-vs-clock-gettime-vs-gettimeof)
// > POSIX.1-2008 says that. "Applications should use the clock_gettime() function instead of the obsolescent gettimeofday() function", so you should stay away from it. Linux x86 and implements it as a system call.
