// https://twitter.com/__phantomderp/status/1484806444981628933
// https://godbolt.org/z/xMh5WYvsf
#include <iostream>

int main () {
    std::cout << -sizeof(int) << std::endl;
    return 0;
}


// Output: ???
// sizeof(int) yields an unsigned result, because I'm negating and unsigned number.
// That is small enough to fit inside of a signed 128 bit integer. So it just rolls with it.
// [What should happen to the negation of a size_t (i.e. `-sizeof(struct foo)`))?](https://stackoverflow.com/questions/1269019/what-should-happen-to-the-negation-of-a-size-t-i-e-sizeofstruct-foo)
