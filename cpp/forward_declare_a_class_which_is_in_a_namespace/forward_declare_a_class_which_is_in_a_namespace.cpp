// 2015-01-28T09:40+08:00
#include <memory>

// Now, I want to forward declare class `HelloWorld` here.
namespace foo {
    namespace bar {
        class HelloWorld;
    }
}

// According to this page:
// [When can I use a forward declaration?](http://stackoverflow.com/questions/553682/when-can-i-use-a-forward-declaration)
// >whether you can use an incomplete type as a template parameter is
// >dependent on the way the type is used in the template.
// >For instance, std::vector<T> requires its parameter to be a complete type,
// >while boost::container::vector<T> does not. Sometimes, a complete type is
// >required only if you use certain member functions; this is the case for
// >std::unique_ptr<T>, for example.
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
// [Forward declaration of nested types/classes in C++](http://stackoverflow.com/questions/951234/forward-declaration-of-nested-types-classes-in-c)
// [How to forward declare a class which is in a namespace](http://stackoverflow.com/questions/19001700/how-to-forward-declare-a-class-which-is-in-a-namespace)
