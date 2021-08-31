#ifndef CLOG_H_
#define CLOG_H_

#include <stdio.h>
#include <stdlib.h>


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

#endif // CLOG_H_

// References:
// https://stackoverflow.com/questions/2124339/c-preprocessor-va-args-number-of-arguments
// https://github.com/Genymobile/scrcpy/blob/master/app/src/util/log.h
// https://github.com/armink/EasyLogger
// https://github.com/tdlib/td/blob/master/td/telegram/Log.h
// https://github.com/GothenburgBitFactory/libshared/blob/591fa58f9c684e22a3a55dbf71bdd00c25ceb28d/src/Log.h
// https://github.com/wiredtiger/wiredtiger/blob/develop/src/log/log.c
// https://github.com/bbc/audiowaveform/blob/master/src/Log.cpp
