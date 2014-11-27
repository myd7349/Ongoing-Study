// 2014-11-27T10:47+08:00

// An example for testing 'throw' keyword in C++.

#include <cassert>
#include <exception>
#include <iostream>
#include <stdexcept>

#define _STR(id) # id
#define STR(id)  _STR(id)

#define SAND_BOX(test_case) \
    do { \
        std::cout << "------------ " << STR(test_case) << " ------------\n"; \
        try { \
            test_case(); \
        } catch (...) { \
        } \
    } while (0)

// C++11 15.1/7:
// If the exception handling mechanism, after completing evaluation of the
// expression to be thrown but before the exception is caught, calls a function
// that exits via an exception, std::terminate is called.
void test_0()
{
    struct C {
        C() {}
        C(const C &) { throw 0; }
    };

    try {
        throw C();
    } catch (C) { // If we wrote "const C &" here, cause no copying operation
                  // happened, then std::terminate would not be called.
    }
}

// C++11 15.1/8:
// A throw-expression with no operand rethrows the currently handled exception
// (15.3). The exception is reactivated with the existing temporary; no new
// temporary exception object is created. The exception is no longer considered
// to be caught; therefore, the value of std::uncaught_exception() will again be
// true.
void test_1()
{
    struct Exception : public std::exception {
        Exception() = default;
        Exception(const Exception &) noexcept {
            std::cout << "std::uncaught_exception() == "
                << std::uncaught_exception() << std::endl;
        }
    };

    try {
        try {
            throw Exception();
        } catch (Exception &e) {
            throw;
        }
    } catch (Exception e) { // The exception object is copied here, so the
                            // copy constructor of Exception will be invoked.
        assert(!std::uncaught_exception());
    }
}

// C++11 15.1/9:
// If no exception is presently being handled, executing a throw-expression with
// no operand calls std:: terminate().
void test_2()
{
    try {
        throw;
    } catch (...) {
    }
}

// Will the resource automatically released if some exception
// is thrown during the using of this resource?
// Answer:
// http://programmers.stackexchange.com/questions/197562/why-is-there-no-finally-construct-in-c
// Note that MSVC has a try-finally extension(__try, __finally) for C/C++:
// http://msdn.microsoft.com/en-us/library/9xtt5hxz.aspx
// C++11 15.2/1:
// As control passes from a throw-expression to a handler, destructors are
// invoked for all automatic objects constructed since the try block was
// entered. The automatic objects are destroyed in the reverse order of the
// completion of their construction.
void test_3()
{
    class Resource {
        int _res_id;
    public:
        ~Resource() {
            std::cout << "~Resource is called: " << _res_id << std::endl;
        }
        Resource(int id) : _res_id(id) {
            std::cout << "Resource() is called: " << _res_id << std::endl;
        }
    };

    // Initialize the resource.
    Resource res0(0), res1(1);

    // Now, something bad happens.
    // So, the question is: will the resource be freed via an invoking of destructor?
    throw std::runtime_error(__func__);
}

int main()
{
    //SAND_BOX(test_0); // terminate called after throwing an instance of 'int'
    SAND_BOX(test_1);
    //SAND_BOX(test_2); // terminate called without an active exception
    SAND_BOX(test_3);

    return 0;
}
