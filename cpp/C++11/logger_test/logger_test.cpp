#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "../../common.h"
#include "../logger.hpp"


int main()
{
    std::mutex mutex;

    std::vector<std::thread> threads;
    
    for (int i = 0; i < 10; ++i)
    {
        threads.push_back(
            std::thread(
                [&mutex](int id)
                {
                    INFOXT(std::cout, mutex, id);
                },
                i
            )
        );
    }

    for (auto &thread : threads)
        thread.join();

    PAUSE();

    return 0;
}
