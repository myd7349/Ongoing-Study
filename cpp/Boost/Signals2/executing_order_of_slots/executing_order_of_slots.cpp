// 2015-01-30T15:51+08:00

// Boost.Signals2 tutorial:
// The "unnamed" slots (i.e., those that have been connected without specifying
// a group name) can be placed at the front or back of the slot list (by passing
// boost::signals2::at_front or boost::signals2::at_back as the last parameter 
// to connect, respectively), and default to the end of the list.

#include <iostream>

#include <boost/signals2.hpp>

#include "../../../common.h"

class Hello {
public:
    void operator()() const {
        std::cout << "Hello, ";
    }
};

class World {
public:
    void operator()() const {
        std::cout << "world!\n";
    }
};

class Buddy {
public:
    void operator()() const {
        std::cout << "Buddy!\n";
    }
};

int main()
{
    boost::signals2::signal<void()> begin_to_learn_programming_signal;

    Hello hello;
    World world;
    Buddy buddy;

    // 1 and 2 are equivalent.
    begin_to_learn_programming_signal.connect(world); // 1
    //begin_to_learn_programming_signal.connect(world, boost::signals2::at_back); // 2

    begin_to_learn_programming_signal.connect(42, hello);
    begin_to_learn_programming_signal.connect(0, buddy);

    begin_to_learn_programming_signal();

    PAUSE();
    return 0;
}