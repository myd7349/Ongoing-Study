#pragma once

#include <cassert>
#include <exception>
#include <mutex>
#include <utility>


template <typename StreamT>
void Log(StreamT &os)
{
}


template <typename StreamT, typename FirstT, typename ...RestT>
void Log(StreamT &os, FirstT &&first, RestT &&...rest)
{
    os << std::forward<FirstT>(first);
    Log(os, std::forward<RestT>(rest)...);
}


template <typename StreamT, typename MutexT, typename FirstT, typename ...RestT>
void LogT(StreamT &os, MutexT &mutex, FirstT &&first, RestT &&...rest)
{
    std::lock_guard<MutexT> lock(mutex);

    os << std::forward<FirstT>(first);
    Log(os, std::forward<RestT>(rest)...);
}



template <typename StreamT, typename CharT, typename FirstT, typename ...RestT>
void LogEx(StreamT &os, const CharT *level, const CharT *fileName, int lineNo, FirstT &&first, RestT &&...rest)
{
    assert(level != nullptr);
    assert(fileName != nullptr);

    os << level << " [" << fileName << ':' << lineNo << ' ';
    os << std::forward<FirstT>(first);
    Log(os, std::forward<RestT>(rest)...);
    os << '\n';
}


template <typename StreamT, typename MutexT, typename CharT, typename FirstT, typename ...RestT>
void LogExT(StreamT &os, MutexT &mutex, const CharT *level, const CharT *fileName, int lineNo, FirstT &&first, RestT &&...rest)
{
    std::lock_guard<MutexT> lock(mutex);

    assert(level != nullptr);
    assert(fileName != nullptr);

    os << level << " [" << fileName << ':' << lineNo << ' ';
    os << std::forward<FirstT>(first);
    Log(os, std::forward<RestT>(rest)...);
    os << '\n';
}


#define DEBUG(os, ...) Log((os), "DEBUG", __FILE__, __LINE__, __VA_ARGS__)
#define INFO(os,  ...) Log((os), "INFO",  __FILE__, __LINE__, __VA_ARGS__)
#define WARN(os,  ...) Log((os), "WARN",  __FILE__, __LINE__, __VA_ARGS__)
#define ERR(os,   ...) Log((os), "ERR",   __FILE__, __LINE__, __VA_ARGS__)
#define FATAL(os, ...) Log((os), "FATAL", __FILE__, __LINE__, __VA_ARGS__)

#define DEBUGT(os, mutex, ...) LogT((os), (mutex), "DEBUG", __FILE__, __LINE__, __VA_ARGS__)
#define INFOT(os,  mutex, ...) LogT((os), (mutex), "INFO",  __FILE__, __LINE__, __VA_ARGS__)
#define WARNT(os,  mutex, ...) LogT((os), (mutex), "WARN",  __FILE__, __LINE__, __VA_ARGS__)
#define ERRT(os,   mutex, ...) LogT((os), (mutex), "ERR",   __FILE__, __LINE__, __VA_ARGS__)
#define FATALT(os, mutex, ...) LogT((os), (mutex), "FATAL", __FILE__, __LINE__, __VA_ARGS__)

#define DEBUGX(os, ...) LogEx((os), "DEBUG", __FILE__, __LINE__, __VA_ARGS__)
#define INFOX(os,  ...) LogEx((os), "INFO",  __FILE__, __LINE__, __VA_ARGS__)
#define WARNX(os,  ...) LogEx((os), "WARN",  __FILE__, __LINE__, __VA_ARGS__)
#define ERRX(os,   ...) LogEx((os), "ERR",   __FILE__, __LINE__, __VA_ARGS__)
#define FATALX(os, ...) LogEx((os), "FATAL", __FILE__, __LINE__, __VA_ARGS__)

#define DEBUGXT(os, mutex, ...) LogExT((os), (mutex), "DEBUG", __FILE__, __LINE__, __VA_ARGS__)
#define INFOXT(os,  mutex, ...) LogExT((os), (mutex), "INFO",  __FILE__, __LINE__, __VA_ARGS__)
#define WARNXT(os,  mutex, ...) LogExT((os), (mutex), "WARN",  __FILE__, __LINE__, __VA_ARGS__)
#define ERRXT(os,   mutex, ...) LogExT((os), (mutex), "ERR",   __FILE__, __LINE__, __VA_ARGS__)
#define FATALXT(os, mutex, ...) LogExT((os), (mutex), "FATAL", __FILE__, __LINE__, __VA_ARGS__)


// References:
// Ongoing-Study/c/clog.h
// ./varadic_template_test
// https://stackoverflow.com/questions/6/374264/is-cout-synchronized-thread-safe
// https://github.com/microsoft/vcpkg/pull/7443
