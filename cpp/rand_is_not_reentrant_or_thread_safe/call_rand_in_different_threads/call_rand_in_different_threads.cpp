// 2015-02-26T08:15+08:00
//
// When learning an example of ZeroMQ in zguide:
// https://github.com/imatix/zguide/blob/master/examples/C/rtreq.c
// I found that it doesn't work as expected in VS2013(Win7 x64):
// https://github.com/imatix/zguide/issues/521
//
// After some boring debugging, I wondered if it is because that
// calling `rand` from multiple threads in MSVC will produce the
// same pseudo random number.
// Again, stackoverflow gave me the answer:
// http://stackoverflow.com/questions/6161322/using-stdlibs-rand-from-multiple-threads

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>

#define CONFIG_USING_BOOST (0)
#include "../../common.h"

#define THREAD_COUNT (10)

#ifndef USING_PTHREADS
# define USING_PTHREADS (1)
#endif

#if USING_PTHREADS // Using PThreads

#include <pthread.h>

#ifdef _MSC_VER
# pragma comment(lib, "pthreadVC2.lib")
#endif

namespace {
pthread_mutex_t g_mtx = PTHREAD_MUTEX_INITIALIZER;

void *thread_routine(void *arg)
{
    std::intptr_t id = (std::intptr_t)arg;

    pthread_mutex_lock(&g_mtx);
    std::cout << '#' << id << ": " << std::rand() << std::endl;
    pthread_mutex_unlock(&g_mtx);

    return NULL;
}
}

int main()
{
    pthread_t threads[THREAD_COUNT];

    for (int i = 0; i < THREAD_COUNT; ++i) {
        int rc = pthread_create(threads + i, NULL, thread_routine, (void *)((intptr_t)i));

        assert(0 == rc);
        if (rc != 0) {
            std::cerr << "Failed to create thread #" << i << '\n';
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < THREAD_COUNT; ++i) {
        void *res;
        int rc = pthread_join(threads[i], &res);

        assert(0 == rc);
        if (rc != 0) {
            std::cerr << "Failed to join thread #" << i << '\n';
            exit(EXIT_FAILURE);
        }

        std::free(res);
    }

    PAUSE();
    return 0;
}

#else // Using C++11 thread

#include <mutex>
#include <thread>
#include <utility>
#include <vector>

namespace {
std::mutex g_mtx;

void thread_routine(std::intptr_t id)
{
    // Guarantee that std::cout is synchronized.
    // http://stackoverflow.com/questions/6374264/is-cout-synchronized-thread-safe
    std::lock_guard<std::mutex> lock(g_mtx);

    // *** Caution: `std::rand()` is not reentrant or thread-safe.
    std::cout << '#' << id << ": " << std::rand() << std::endl;
}
}

int main()
{
    std::vector<std::thread> threads;

    for (int i = 0; i < THREAD_COUNT; ++i) {
        threads.push_back(std::move(std::thread(thread_routine, static_cast<std::intptr_t>(i)))); // ???
    }

    for (auto &t : threads) {
        t.join();
    }

    PAUSE();
    return 0;
}

#endif

/*
Output(Win7 x64 + VS2013 + pthreads):
#0: 41
#6: 41
#7: 41
#3: 41
#9: 41
#2: 41
#8: 41
#5: 41
#4: 41
#1: 41
Output(Win7 x64 + VS2013/GCC 4.8.1 + C++11 thread):
#0: 41
#1: 41
#2: 41
#3: 41
#4: 41
#5: 41
#6: 41
#7: 41
#8: 41
#9: 41
Output(CentOS x86_64 + GCC 4.4.7 + -lpthread):

Output(CentOS x86_64 + GCC 4.4.7 + C++0x thread):
Segmentation fault (core dumped)
*/

// References:
// [is it necessary to call pthread_join()](http://stackoverflow.com/questions/10600250/is-it-necessary-to-call-pthread-join)
// [pthread_create](http://man7.org/linux/man-pages/man3/pthread_create.3.html)
// [pthread_join](http://man7.org/linux/man-pages/man3/pthread_join.3.html)
