// 2014-08-12T16:25+08:00
// http://en.wikipedia.org/wiki/C%2B%2B11
// http://blog.csdn.net/gzlaiyonghao/article/details/6564162
//
// 2014-08-23T22:02+08:00
// http://stackoverflow.com/questions/12190051/member-initialization-while-using-delegated-constructor
#include <iostream>

class SomeType {
    int number;
public:
    SomeType(int new_number) : number(new_number) {};
    SomeType() : SomeType(42) {}

    // 2014-08-14T09:00+08:00
    // ISO C++ 11, 12.6.2/6
    // If a mem-initializer-id designates the constructor’s class,
    // it shall be the only mem-initializer; the constructor is a
    // delegating constructor, and the constructor selected by
    // the mem-initializer is the target constructor .
    //
    // error message produced by g++:
    // error: mem-initializer for 'SomeType::number' follows constructor delegation
    //
    // 我认为这是一种很好的处理方法，因为既然一个delegating constructor
    // 调用target constructor来完成构造工作，那么表明在target constructor
    // 中，所有的成员都会被正确地初始化。所以，在delegating constructor
    // 调用target constructor的时候，后面无需跟其它mem-initializer了。
    //
    //SomeType(double dbl) : SomeType((int)dbl), number(dbl) {}

    int get() const { return number; }
};

int main()
{
    SomeType obj;
    std::cout << obj.get() << std::endl;

    return 0;
}
