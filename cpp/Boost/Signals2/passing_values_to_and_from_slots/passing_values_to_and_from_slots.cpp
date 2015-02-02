// 2015-01-30T16:33+08:00

// This is an example that demonstrates how to pass values to and from slots.
// Most code in this example is based on those code snippets in Boost.Signals2's
// tutorial.

#include <cassert>
#include <iostream>
#include <vector>

#include <boost/signals2.hpp>

#include "../../../common.h"
#include "../../../uniform_typename/uniform_typename.h"

double product(double x, double y) { return x * y; }
double quotient(double x, double y) { assert(y != 0.0); return x / y; }
double sum(double x, double y) { return x + y; }
double difference(double x, double y) { return x - y; }

namespace pass_values_to_slots {
void print_args(double x, double y)
{
    std::cout << "The arguments are " << x << " and " << y << std::endl;
}

void print_sum(double x, double y)
{
    std::cout << "The sum is " << sum(x, y) << std::endl;
}

void print_product(double x, double y)
{
    std::cout << "The product is " << product(x, y) << std::endl;
}

void print_difference(double x, double y)
{
    std::cout << "The difference is " << difference(x, y) << std::endl;
}

void print_quotient(double x, double y)
{
    std::cout << "The quotient is " << quotient(x, y) << std::endl;
}

void test()
{
    boost::signals2::signal<void(double, double)> sig;

    sig.connect(&print_args);
    sig.connect(&print_sum);
    sig.connect(&print_product);
    sig.connect(&print_difference);
    sig.connect(&print_quotient);

    sig(5., 3.);
}
}

namespace signal_return_values {
void test()
{
    boost::signals2::signal<double(double, double)> sig;

    sig.connect(&product);
    sig.connect(&quotient);
    sig.connect(&sum);
    sig.connect(&difference);

    // The default behaviour of a signal that has a return type is to call all 
    // values and then return a boost::optional containing the result returned
    // by the last slot called.
    std::cout << TYPE_NAME(sig(5., 3.)) << std::endl; // class boost::optional<double>
    std::cout << *sig(5, 3) << std::endl;
}
}

namespace maximum_value_returned_by_slots {
// combiner which returns the maximum value returned by all slots
template <typename T>
struct maximum
{
    typedef T result_type;

    template <typename InputIterator>
    T operator()(InputIterator first, InputIterator last) const
    {
        // If there are no slots to call, just return the
        // default-constructed value
        if (first == last) {
            return T();
        }
        T max_value = *first++;
        while (first != last) {
            if (max_value < *first) {
                max_value = *first;
            }
            ++first;
        }
        return max_value;
    }
};

void test()
{
    boost::signals2::signal<double(double, double), maximum<double>> sig;

    sig.connect(&product);
    sig.connect(&quotient);
    sig.connect(&sum);
    sig.connect(&difference);

    std::cout << "maximum: " << sig(5, 3) << std::endl;
}
}

namespace coalesce_values_returned_by_slots {
// aggregate_values is a combiner which places all the values returned
// from slots into a container
template <typename Container>
struct aggregate_values {
    typedef Container result_type;

    template <typename InputIterator>
    Container operator()(InputIterator first, InputIterator last) const
    {
        Container values;

        while (first != last) {
            values.push_back(*first);
            ++first;
        }

        return values;
    }
};

void test()
{
    boost::signals2::signal<double(double, double), aggregate_values<std::vector<double>>> sig;

    sig.connect(&product);
    sig.connect(&quotient);
    sig.connect(&sum);
    sig.connect(&difference);

    Println(sig(5, 3));
}
}

int main()
{
    SPLIT_LINE0();
    pass_values_to_slots::test();

    SPLIT_LINE0();
    signal_return_values::test();

    SPLIT_LINE0();
    maximum_value_returned_by_slots::test();

    SPLIT_LINE0();
    coalesce_values_returned_by_slots::test();

    PAUSE();
    return 0;
}

// References:
// [Boost.Signals2 Tutorial](http://www.boost.org/doc/libs/1_57_0/doc/html/signals2/tutorial.html)
