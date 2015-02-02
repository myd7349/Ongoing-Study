// 2015-02-02T10:07+08:00
// Signal-slot connection management test.
// This example is based on those code snippets in Boost.Signals2's tutorial.

#include <iostream>

#include <boost/signals2.hpp>

#include "../../../common.h"
#include "../../../dividing_lines.h"

struct HelloWorld {
    void operator()() const {
        std::cout << "Hello, world!" << std::endl;
    }
};

namespace disconnecting_slots {
void test()
{
    boost::signals2::signal<void()> sig;
    
    boost::signals2::connection c = sig.connect(HelloWorld());
    std::cout << "c is connected\n";
    sig();

    c.disconnect();
    std::cout << "c is disconnected\n";
    sig();
}
}

namespace blocking_slots {
void test()
{
    boost::signals2::signal<void()> sig;
    boost::signals2::connection c = sig.connect(HelloWorld());
    sig();

    {
        boost::signals2::shared_connection_block block(c); // block the slot
        std::cout << "c is blocked.\n";
        sig(); // No output: the slot is blocked
    }

    std::cout << "c is not blocked.\n";
    sig();
}
}

namespace scoped_connection {
void test()
{
    boost::signals2::signal<void()> sig;
    {
        boost::signals2::scoped_connection c(sig.connect(HelloWorld()));
        sig();
    }
    sig();
}
}

int main()
{
    DIVIDING_LINE('-');
    disconnecting_slots::test();

    DIVIDING_LINE('-');
    blocking_slots::test();

    DIVIDING_LINE('-');
    scoped_connection::test();

    PAUSE();
    return 0;
}
