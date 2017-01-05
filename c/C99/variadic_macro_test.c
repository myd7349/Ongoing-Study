// 2017-01-05T17:59:53+08:00
#include <stdio.h>

#define CALL(fn, ...) fn(__VA_ARGS__)

void foo()
{
    printf("42\n");
}

int main()
{
    // 1.
    CALL(foo);
    CALL(foo, );
    
    // 2.
    CALL(printf, "Hello, world!\n");
    //CALL(printf, "Hello, world!\n", ); // error: expected expression before ')' token

    return 0;
}

// References:
// [Is it possible to prevent the removal of the comma with empty __VA_ARGS__ in Visual C++?](http://stackoverflow.com/questions/7103824/is-it-possible-to-prevent-the-removal-of-the-comma-with-empty-va-args-in-vis)
// [3.6 Variadic Macros](https://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html)
// [Variadic macros with zero arguments](http://stackoverflow.com/questions/5891221/variadic-macros-with-zero-arguments)
// pybind11.pdf 7.2 Combining virtual functions and inheritance

// The implementation of PYBIND11_OVERLOAD uses __VA_ARGS__.
// So, for a method that with an empty argument list:
//     1. PYBIND11_OVERLOAD(std::string, Animal, name, ); // OK
//     2. PYBIND11_OVERLOAD(std::string, Animal, name); // OK
// for a method that accepts one or more arguments, however:
//     1. PYBIND11_OVERLOAD_PURE(std::string, Dog, go, n_times); // OK
//     2. PYBIND11_OVERLOAD_PURE(std::string, Dog, go, n_times, ); // not OK
// If you didn't know this and a redundant comma is added after n_times, 
// the compiler(MSVC, for example) will give you a lot of error messages.
// Only God can understand compilation errors related to C++ template.
