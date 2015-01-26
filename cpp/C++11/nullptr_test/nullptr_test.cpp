// 2015-01-26T15:42+08:00

// ISO IEC 14882 2011(C++11):
// 2.14.7 Pointer literals
// The pointer literal is the keyword nullptr.
// It is a prvalue of type std::nullptr_t.
//
// prvalue: "pure" rvalue
// http://en.cppreference.com/w/cpp/language/value_category
//
// cppreference:
// http://en.cppreference.com/w/cpp/language/reinterpret_cast
// Note that the null pointer constant nullptr or any other value of type
// std::nullptr_t cannot be converted to a pointer with reinterpret_cast:
// implicit conversion or static_cast should be used for this purpose.

#include <cstdio>

void foo(const bool *)
{
}

void foo(const int *)
{
}

void bar(int *)
{
    std::printf("bar(int *)\n");
}

void bar(int)
{
    std::printf("bar(int)\n");
}

int main()
{
    // -------- Test 0 --------
    // Ambiguous!
    //foo(nullptr);

    // error: invalid cast from type 'std::nullptr_t' to type 'bool*'
    //foo(reinterpret_cast<bool *>(nullptr));

    foo((const bool *)nullptr);
    foo(static_cast<const bool *>(nullptr));

    // -------- Test 1 --------
    bar(NULL); // Oops! Not what we want.
    bar(nullptr); // Now, life becomes beautiful!

    // To be continued...

    return 0;
}
