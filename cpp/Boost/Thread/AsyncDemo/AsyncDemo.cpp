#include <iostream>

#include <boost/thread/externally_locked_stream.hpp>
#include <boost/thread/future.hpp>

#include "../../../common.h"


int main()
{
    boost::recursive_mutex mutex;
    boost::externally_locked_stream<std::ostream> aout(std::cout, mutex); // C++ Actor Framework - aout

    for (int i = 0; i < 10; ++i)
    {
        boost::async(boost::launch::any,
            [&aout, i]() { aout << '#' << i << " Hello, world from thread " << boost::this_thread::get_id() << '\n'; });
    }

    PAUSE();

    return 0;
}


// References:
// Ongoing-Study/cpp/C++11/create10threads
