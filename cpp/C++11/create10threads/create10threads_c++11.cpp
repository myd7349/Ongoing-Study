// 2014-04-07T17:12+08:00
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::mutex mtx;

void print_hello_world(int tid)
{
    std::lock_guard<std::mutex> lck(mtx);
    std::cout << "Hello, world. Greeting from thread "
        << tid << " (" << std::this_thread::get_id()
        << ")" << std::endl;
}

int main()
{
    std::vector<std::thread> threads;
    const int number_of_threads = 10;

    for (int i = 0; i < number_of_threads; ++i) {
        threads.push_back(std::thread(print_hello_world, i));
    }

    for (auto &tid : threads) {
        tid.join();
    }

    return 0;
}

