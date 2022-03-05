#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif


int main(void)
{
#ifdef _WIN32
    SYSTEMTIME st;
#endif

    time_t t = time(NULL);
    struct tm lt;

#ifdef _MSC_VER
    /* The implementation of localtime_s in Microsoft CRT is incompatible with
       the C standard since it has reversed parameter order and returns errno_t. */
    localtime_s(&lt, &t);
#else
#ifdef __STDC_LIB_EXT1__
    localtime_s(&t, &lt);
#else
#pragma message "__STDC_LIB_EXT1__ is not available."
    /* According to POSIX.1-2004, localtime() is required to behave as though
       tzset(3) was called, while localtime_r() does not have this requirement.
       For portable code tzset(3) should be called before localtime_r().  */
    //localtime_r(&t, &lt);

    lt = *localtime(&t);
#endif
#endif

    printf("%d-%02d-%02dT%02d:%02d:%02d\n",
        lt.tm_year + 1900,
        lt.tm_mon + 1,
        lt.tm_mday,
        lt.tm_hour,
        lt.tm_min,
        lt.tm_sec);

#ifdef _WIN32
    GetLocalTime(&st);
    printf("%d-%02d-%02dT%02d:%02d:%02d\n",
        st.wYear,
        st.wMonth,
        st.wDay,
        st.wHour,
        st.wMinute,
        st.wSecond); 
#endif

    return 0;
}


// References:
// https://en.cppreference.com/w/c/chrono/localtime
// https://en.cppreference.com/w/c/chrono/tm
// [C++: location of localtime_s in GCC](https://stackoverflow.com/questions/69992446/c-location-of-localtime-s-in-gcc)
// https://github.com/gabime/spdlog/issues/392
// https://linux.die.net/man/3/localtime_r
