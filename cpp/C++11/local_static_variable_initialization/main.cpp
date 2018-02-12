// 2018-02-12T09:38+08:00
#include <iostream>
#include <thread>


#define ENTER_FUNC() do { std::cout << __LINE__ << " Enter " << __func__ << std::endl; } while (0)
#define LEAVE_FUNC() do { std::cout << __LINE__ << " Leave " << __func__ << std::endl; } while (0)


struct MyClass
{
    MyClass()
    {
        std::cout << "Constructing MyClass" << std::endl;
    }
};


const MyClass &CreateMyClass()
{
    ENTER_FUNC();
    static MyClass myClass;
    LEAVE_FUNC();
    return myClass;
}


int main()
{
    ENTER_FUNC();

    std::thread thrd1(CreateMyClass);
    std::thread thrd2(CreateMyClass);

    thrd1.join();
    thrd2.join();

    LEAVE_FUNC();

    return 0;
}

// References:
// https://www.zhihu.com/question/267013757
// https://stackoverflow.com/questions/1661529/is-meyers-implementation-of-the-singleton-pattern-thread-safe
// https://gcc.gnu.org/ml/gcc-patches/2004-09/msg00265.html
// https://stackoverflow.com/questions/12186857/on-local-and-global-static-variables-in-c
