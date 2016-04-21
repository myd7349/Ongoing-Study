// 2016-04-21T15:56+08:00
// SWIG Documentation:
// In this code, both A_function() and B_function() may legally accept an object
// of type C * (via inheritance). However, one of the functions will always
// return the wrong result when used as shown. The reason for this is that even
// though p points to an object of type C, the casting operation doesn't work like
// you would expect. Internally, this has to do with the data representation of C.
// With multiple inheritance, the data from each base class is stacked together.#if 0
----- <--- (C *) , (A *)
| A |
|---| <--- (B *)
| B |
------------
#endif
// Because of this stacking, a pointer of type C * may change value when it is
// converted to a A * or B * . However, this adjustment does not occur if you are
// converting from a void * .

#include <iostream>

class A {
public:
    int x = 0;
};

class B {
public:
    int y = 42;
};

class C : public A, public B {
};

void A_function(A *a)
{
    std::cout << "Address: " << static_cast<void *>(a) << ", A::x: " << a->x << std::endl;
}

void B_function(B *b)
{
    std::cout << "Address: " << static_cast<void *>(b) << ", B::y: " << b->y << std::endl;
}

C c;

void test_0()
{
    void *p = &c;

    A_function((A *)p);
    B_function((B *)p);
}

void test_1()
{
    C *p = &c;

    A_function((A *)p);
    B_function((B *)p);
}

int main()
{
    test_0();
    test_1();

    return 0;
}

// References:
// SWIGDocumentation.pdf
//   -- 6.14 A brief discussion of multiple inheritance, pointers, and type checking
// https://www.zhihu.com/question/30418880
// [When to use reinterpret_cast?](http://stackoverflow.com/questions/573294/when-to-use-reinterpret-cast)
