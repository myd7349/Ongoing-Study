// 2015-04-22T15:48+08:00
// C99 does support single line comments.

#include <stdio.h>

typedef struct {
    double PI;
    double TAO;
} MagicMath;

void haha(MagicMath m)
{
    printf("PI: %g, TAO: %g\n", m.PI, m.TAO);
}

void test_0(void)
{
    MagicMath m = {};
    haha(m);
}

void test_1(void)
{
    MagicMath m = {.TAO = 6.28}; // designated initializer
    haha(m);
}

void test_2(void)
{
    MagicMath m;

    m = (MagicMath){.PI = 3.14}; // compound literal
    haha(m);

    m = (MagicMath){3.1415};
    haha(m);
}

void test_3(void)
{
    MagicMath m = {3.14, m.PI * 2.0}; // ???
    haha(m);

    // We can't do this.
    //MagicMath m2 = {.TAO = 6.28, .PI = .TAO / 2};
    //haha(m2);
}

int main(void)
{
    test_0();
    test_1();
    test_2();
    test_3();

    return 0;
}

/*
 * References:
 * [C++ Structure Initialization](http://stackoverflow.com/questions/11516657/c-structure-initialization)
 * [How to initialize a struct in ANSI C](http://stackoverflow.com/questions/330793/how-to-initialize-a-struct-in-ansi-c)
 * [Is int main() { } (without “void”) valid and portable in ISO C?](http://stackoverflow.com/questions/29190986/is-int-main-without-void-valid-and-portable-in-iso-c)
 * [Single line comments in Ansi-C](http://stackoverflow.com/questions/8284940/single-line-comments-in-ansi-c)
 * [Struct and union initialization](http://en.cppreference.com/w/c/language/struct_initialization)
 */
