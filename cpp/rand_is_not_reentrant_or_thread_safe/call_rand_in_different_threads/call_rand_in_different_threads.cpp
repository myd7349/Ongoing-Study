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

#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>

#define CONFIG_USING_BOOST (0)
#include "../../common.h"

std::mutex g_mtx;

void thread_routine()
{
    // Guarantee that std::cout is synchronized.
    // http://stackoverflow.com/questions/6374264/is-cout-synchronized-thread-safe
    std::lock_guard<std::mutex> lock(g_mtx);

    // *** Caution: `std::rand()` is not reentrant or thread-safe.
    std::cout << std::rand() << std::endl;
}

int main()
{
    for (int i = 0; i < 10; ++i) {
        std::thread(thread_routine).join();
    }

    PAUSE();
    return 0;
}

/*
Output(Win7 x64 + VS2013):
41
41
41
41
41
41
41
41
41
41
Output(Win7 x64 + GCC 4.8.1):
41
41
41
41
41
41
41
41
41
41
Output(CentOS + GCC 4.4.7, g++ -std=c++0x call_rand_in_different_threads.cpp):
Segmentation fault (core dumped)
*/
