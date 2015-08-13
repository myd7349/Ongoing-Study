// 2015-08-13T09:21+08:00
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <new>

// Note the difference between:
// 1. new operator
// 2. operator new
// The latter only cares how to allocate raw memory.
// The former, however, will also take charge of constructing
// the object(s) on that raw memory.

// When we say: overloading a new operator, we in fact are 
// `replacing` the default new operator. That is, we don't
// need to care about how to invoke a proper constructor to
// construct the object(s) in our overloaded version.

#if 0
struct Dummy {};

void *operator new(std::size_t size, Dummy)
{
    std::printf("%s(): %zd\n", __func__, size);

    void *ptr = ::operator new(size);
    return ptr;
}

void *operator new[](std::size_t size, Dummy)
{
    std::printf("%s(): %zd\n", __func__, size);

    void *ptr = ::operator new(size);
    return ptr;
}

#define new new(Dummy())
#else
void *operator new(std::size_t size)
{
    std::printf("%s(): %zd\n", __func__, size);

    void *ptr = std::malloc(size);
    return ptr;
}

void *operator new[](std::size_t size)
{
    std::printf("%s(): %zd\n", __func__, size);

    void *ptr = std::malloc(size);
    return ptr;
}
#endif

typedef int Coord3d[3];

struct Integer {
    Integer(int i) : i_(i) { std::printf("%s(): %d\n", __func__, i_); }
    ~Integer() { std::printf("%s(): %d\n", __func__, i_); }
private:
    int i_;
};

int main()
{
    int *coord = new Coord3d {1, 2, 3}; // new? new[]?
    std::printf("(%d,%d,%d)\n", coord[0], coord[1], coord[2]);
    delete[] coord; // Any question?

    delete[] new Integer[3] {0, 1, 2};

    return 0;
}

// References:
// Effective C++ 3E: Item 16
// [The many faces of operator new in C++ ](http://eli.thegreenplace.net/2011/02/17/the-many-faces-of-operator-new-in-c)
// [Difference between 'new operator' and 'operator new'?](http://stackoverflow.com/questions/1885849/difference-between-new-operator-and-operator-new)
// [How do I call the original ¡°operator new¡± if I have overloaded it?](http://stackoverflow.com/questions/4134195/how-do-i-call-the-original-operator-new-if-i-have-overloaded-it)
// [Overloading of operator new in C++](http://stackoverflow.com/questions/28955526/overloading-of-operator-new-in-c)
// [overloading new/delete](http://stackoverflow.com/questions/583003/overloading-new-delete)
// [My Rant on C++'s operator new](http://www.scs.stanford.edu/~dm/home/papers/c++-new.html)
