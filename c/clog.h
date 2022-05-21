#ifndef CLOG_H_
#define CLOG_H_

#include <stdio.h>
#include <stdlib.h>


#if defined(_MSC_VER)

#define CLOG_IMPL(level, fmt, ...) \
    do \
    { \
        fprintf(stderr, #level " [%s:%d] " fmt "\n", __FILE__, __LINE__, __VA_ARGS__); \
        if (#level[0] == 'F') \
            exit(1); \
    } while (0)

#define DEBUG(fmt, ...) CLOG_IMPL(D, fmt, __VA_ARGS__)
#define INFO(fmt, ...)  CLOG_IMPL(I, fmt, __VA_ARGS__)
#define WARN(fmt, ...)  CLOG_IMPL(W, fmt, __VA_ARGS__)
#define ERR(fmt, ...)   CLOG_IMPL(E, fmt, __VA_ARGS__)
#define FATAL(fmt, ...) CLOG_IMPL(F, fmt, __VA_ARGS__)

#define CLOG(level, fmt, ...) level(fmt, __VA_ARGS__)

#elif defined(__GNUC__)

#define CLOG_IMPL(level, fmt, ...) \
    do \
    { \
        fprintf(stderr, #level " [%s:%d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
        if (#level[0] == 'F') \
            exit(1); \
    } while (0)

#define DEBUG(fmt, ...) CLOG_IMPL(D, fmt, ##__VA_ARGS__)
#define INFO(fmt, ...)  CLOG_IMPL(I, fmt, ##__VA_ARGS__)
#define WARN(fmt, ...)  CLOG_IMPL(W, fmt, ##__VA_ARGS__)
#define ERR(fmt, ...)   CLOG_IMPL(E, fmt, ##__VA_ARGS__)
#define FATAL(fmt, ...) CLOG_IMPL(F, fmt, ##__VA_ARGS__)

#define CLOG(level, fmt, ...) level(fmt, ##__VA_ARGS__)

#else
    
#error Not tested yet.

#endif

#endif // CLOG_H_

// References:
// https://stackoverflow.com/questions/2124339/c-preprocessor-va-args-number-of-arguments
// https://github.com/Genymobile/scrcpy/blob/master/app/src/util/log.h
// https://github.com/armink/EasyLogger
// https://github.com/tdlib/td/blob/master/td/telegram/Log.h
// https://github.com/GothenburgBitFactory/libshared/blob/591fa58f9c684e22a3a55dbf71bdd00c25ceb28d/src/Log.h
// https://github.com/wiredtiger/wiredtiger/blob/develop/src/log/log.c
// https://github.com/bbc/audiowaveform/blob/master/src/Log.cpp
// https://github.com/MaskRay/ell/blob/master/ell/log.h
// https://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html
// [Standard alternative to GCC's ##__VA_ARGS__ trick?](https://stackoverflow.com/questions/5588855/standard-alternative-to-gccs-va-args-trick)
// [What does ##__VA_ARGS__ mean?](https://stackoverflow.com/questions/52891546/what-does-va-args-mean)
// > C++20 introduced __VA_OPT__ for this purpose: https://en.cppreference.com/w/cpp/preprocessor/replace.
// [Appending to __VA_ARGS__](https://stackoverflow.com/questions/4054085/appending-to-va-args)
// https://github.com/cofyc/dnscrypt-wrapper/blob/master/logger.h
