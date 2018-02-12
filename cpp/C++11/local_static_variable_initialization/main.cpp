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

    // https://stackoverflow.com/questions/7422081/does-clang-do-threadsafe-initialisation-of-local-static-variables
    // metions the `-fno-threadsafe-statics` option.
    //
    // https://gcc.gnu.org/onlinedocs/gcc/C_002b_002b-Dialect-Options.html
    // -fno-threadsafe-statics
    //     Do not emit the extra code to use the routines specified in the C++ ABI for thread-safe initialization of local statics.
    //     You can use this option to reduce code size slightly in code that doesn’t need to be thread-safe.

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
// https://stackoverflow.com/questions/12186857/on-local-and-global-static-variables-in-c
// http://clang.llvm.org/docs/ThreadSafetyAnalysis.html
// https://github.com/llvm-mirror/clang/commit/4ea46f54b3ccd6d1e9f305058ae8b8664033131a
