#pragma once

#if !defined(FOUND_PTHREADS) || !FOUND_PTHREADS
# error PThreads not found!
#endif

#include <cassert>
#include <cstddef>
#include <iosfwd>
#include <stdexcept>

#include <pthread.h>

#include "../../../cpp/common.h"
#include "ProducerConsumerContextBase.hpp"


#define CHECKED_PTHREAD_CALL_BEGIN(func, ...) \
    if (auto result = func(__VA_ARGS__)) \
    { \
        Log(STR(func) " failed: ", result);
#define CHECKED_PTHREAD_CALL_END() \
    }

#define CHECKED_PTHREAD_CALL(func, ...) \
CHECKED_PTHREAD_CALL_BEGIN(func, __VA_ARGS__) \
    throw std::runtime_error(STR(func)); \
CHECKED_PTHREAD_CALL_END()

#define CHECKED_PTHREAD_CALL_NOTHROW(func, ...) \
CHECKED_PTHREAD_CALL_BEGIN(func, __VA_ARGS__) \
CHECKED_PTHREAD_CALL_END()


class ProducerConsumerContextPThreads final : public ProducerConsumerContextBase
{
public:
    ProducerConsumerContextPThreads(std::size_t bufferSize, std::ostream &os, bool enableLogging)
        : ProducerConsumerContextBase(bufferSize, os, enableLogging)
    {
        CHECKED_PTHREAD_CALL(pthread_mutex_init, &mutex_, nullptr);
        CHECKED_PTHREAD_CALL(pthread_cond_init, &empty_, nullptr);
        CHECKED_PTHREAD_CALL(pthread_cond_init, &fill_, nullptr);
    }

    ~ProducerConsumerContextPThreads()
    {
        CHECKED_PTHREAD_CALL_NOTHROW(pthread_mutex_destroy, &mutex_);
        CHECKED_PTHREAD_CALL_NOTHROW(pthread_cond_destroy, &empty_);
        CHECKED_PTHREAD_CALL_NOTHROW(pthread_cond_destroy, &fill_);
    }

    void Produce(const int *items, std::size_t &count) override
    {
        assert(count <= buffer_.Capacity());

        Log("Producer is trying to get the lock...\n");

        CHECKED_PTHREAD_CALL(pthread_mutex_lock, &mutex_);
        while (buffer_.Full())
            CHECKED_PTHREAD_CALL(pthread_cond_wait, &empty_, &mutex_);

        count = std::min<std::size_t>(count, buffer_.Reserve());

        Log("Producer gets the lock...\n");

        assert(ValidateSize());
        buffer_.PushBackMany(items, count);

        Log("Produce ", count, " items.\n");

        CHECKED_PTHREAD_CALL(pthread_cond_signal, &fill_);
        CHECKED_PTHREAD_CALL(pthread_mutex_unlock, &mutex_);
    }

    void Consume(int *items, std::size_t &count) override
    {
        assert(count <= buffer_.Capacity());

        Log("\tConsumer is trying to get the lock...\n");

        CHECKED_PTHREAD_CALL(pthread_mutex_lock, &mutex_);
        while (buffer_.Empty())
            CHECKED_PTHREAD_CALL(pthread_cond_wait, &fill_, &mutex_);

        count = std::min<std::size_t>(count, buffer_.Size());

        Log("\tConsumer gets the lock...\n");

        assert(ValidateSize());
        buffer_.PopFrontMany(items, count);

        Log("\tConsume ", count, " items.\n");

        CHECKED_PTHREAD_CALL(pthread_cond_signal, &empty_);
        CHECKED_PTHREAD_CALL(pthread_mutex_unlock, &mutex_);
    }

private:
    pthread_mutex_t mutex_;
    pthread_cond_t empty_;
    pthread_cond_t fill_;
};


// References:
// [0] http://pages.cs.wisc.edu/~remzi/OSTEP/threads-cv.pdf
// Operating Systems: Three Easy Pieces, P352
// https://linux.die.net/man/3/pthread_mutex_init
// https://linux.die.net/man/3/pthread_cond_init
// https://linux.die.net/man/3/pthread_mutex_lock
// https://linux.die.net/man/3/pthread_cond_wait
// https://linux.die.net/man/3/pthread_cond_signal
// https://linux.die.net/man/3/pthread_mutex_unlock
// https://linux.die.net/man/3/pthread_mutex_destroy
// https://stackoverflow.com/questions/17169697/how-to-correctly-destroy-pthread-mutex
