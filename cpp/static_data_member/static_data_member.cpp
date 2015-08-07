// 2015-08-07T09:00+08:00
// ISO/IEC 14882:2011(E) 
// This is an example in 9.4/3.

#include <iostream>

int g() { return 998; }
struct X {
    static int g() {
        return 42;
    }
};
struct Y : X {
    static int i;
};

// 9.4.2/2
// The initializer expression in the definition of a static data member is in
// the scope of its class.
#ifdef USE_GLOBAL_G
int Y::i = ::g();
#else
int Y::i = g(); // equivalent to Y::g();
#endif

int main()
{
    std::cout << Y::i << std::endl;
    return 0;
}
