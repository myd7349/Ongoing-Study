// 2015-01-28T09:40+08:00
#include <memory>

// Now, I want to forward declare class `HelloWorld` here.
namespace foo {
    namespace bar {
        class HelloWorld;
    }
}

//
std::shared_ptr<foo::bar::HelloWorld> haha;

// Since now, we can see the definition of class `HelloWorld`
// and we are able to  instantiate `haha` with something meaningful.
#include "hello_world.h"

int main()
{
    haha.reset(new foo::bar::HelloWorld);
    haha->say();

    return 0;
}

// References:
// [How to forward declare a class which is in a namespace](http://stackoverflow.com/questions/19001700/how-to-forward-declare-a-class-which-is-in-a-namespace)
