#ifndef HELLO_WORLD_H_INCLUDED
#define HELLO_WORLD_H_INCLUDED

#include <iostream>

namespace foo {
    namespace bar {
        class HelloWorld {
        public:
            void say() {
                std::cout << "Hello, world!\n";
            }
        };
    }
}

#endif // HELLO_WORLD_H_INCLUDED
