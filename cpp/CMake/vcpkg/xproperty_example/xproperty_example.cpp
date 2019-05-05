#include <iostream>
#include <stdexcept>

#include <xproperty/xobserved.hpp>
#include <xproperty/xproperty.hpp>


struct Foo : public xp::xobserved<Foo>
{
    XPROPERTY(double, Foo, bar);
    XPROPERTY(double, Foo, baz);
};


int main()
{
    Foo foo;

    XOBSERVE(foo, bar, [](Foo &f)
    {
        std::cout << "Observer: New value of bar: " << f.bar << std::endl;
    }
    );

    XVALIDATE(foo, bar, [](Foo &, double &proposal)
    {
        std::cout << "Validator: Proposal: " << proposal << std::endl;
        if (proposal < 0)
        {
            throw std::runtime_error("Only non-negative values are valid.");
        }
        return proposal;
    });

    foo.bar = 1.0;
    std::cout << foo.bar << std::endl;

    try
    {
        foo.bar = -1.0;
    }
    catch (...)
    {
        std::cout << foo.bar << std::endl;
    }

    Foo source, target;
    source.bar = 1.0;

    // Link `source.bar` and `target.baz`
    XDLINK(source, bar, target, baz);

    source.bar = 2.0;
    std::cout << target.baz << std::endl;    // Outputs 2.0

    return 0;
}


// References:
// https://github.com/QuantStack/xproperty
