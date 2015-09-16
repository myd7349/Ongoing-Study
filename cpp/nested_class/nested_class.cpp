// 2015-09-16T10:39+08:00

#include <iostream>

class Enclosing {
    int n_ = 100;
public:
    // A nested class or inner class
    struct Nested {
        Nested(int n);
        Nested(Enclosing &e);
    };
};

Enclosing::Nested::Nested(int n)
{
    // error: invalid use of non-static data member 'Enclosing::n_'
#if 0
    n_ = n;
#endif
}

Enclosing::Nested::Nested(Enclosing &e)
{
    std::cout << e.n_ << std::endl;
}

int main()
{
    Enclosing enclosing;
    Enclosing::Nested nested(enclosing);
    return 0;
}

// References:
// [Nested class' access to enclosing class' private data members](http://stackoverflow.com/questions/1604853/nested-class-access-to-enclosing-class-private-data-members)
// [cppreference - nested classes](http://en.cppreference.com/w/cpp/language/nested_types)
