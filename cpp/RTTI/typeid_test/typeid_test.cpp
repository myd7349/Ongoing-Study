// 2015-03-06T08:35+08:00
#include <iomanip>
#include <iostream>
#include <typeinfo>

#include "../../common.h"
#include "../../uniform_typename/uniform_typename.h"

class Base {
public:
    virtual void foo() {}
};

class Derived : public Base {
public:
    void foo() {}
};

#define TEST_CASE(expr) \
    std::cout << std::boolalpha << STR(expr) << " // " << (expr) << std::endl

#define DUMP_TYPENAME(expr) \
    std::cout << "typeid(" << STR(expr) << ").name() // " << TYPE_NAME(expr) << std::endl

int foo() { return 1; }

int main()
{
    Derived d;
    Base *pb = &d;

    TEST_CASE(typeid(pb) == typeid(Base *));
    TEST_CASE(typeid(pb) == typeid(Derived *));
    TEST_CASE(typeid(*pb) == typeid(Base));
    TEST_CASE(typeid(*pb) == typeid(Derived));

    // 2015-08-26T21:57+08:00
    // https://en.wikibooks.org/wiki/C%2B%2B_Programming/RTTI#Limitations
    // Note that references to pointers will not work under RTTI:
    DUMP_TYPENAME(int *&);

    // ISO/IEC 14882:2011(E) 5.2.8/3
    // When typeid is applied to an expression other than a glvalue of a polymorphic
    // class type, the result refers to a std::type_info object representing the static 
    // type of the expression. Lvalue-to-rvalue(4.1), array-to-pointer(4.2), and 
    // function-to-pointer(4.3) conversions are not applied to the expression.
    int a[2];
    DUMP_TYPENAME(a);
    DUMP_TYPENAME(&a);
    int b[2][3];
    DUMP_TYPENAME(b);
    DUMP_TYPENAME(&b[0]);
    DUMP_TYPENAME(&b[0][0]);
    // http://stackoverflow.com/questions/3000138/can-typeid-be-used-to-pass-a-function
    // Can typeid() be used to pass a function?
    // Meanwhile, typeid(&foo) will give you a function pointer type id, which is different from typeid(foo).
    DUMP_TYPENAME(foo);
    DUMP_TYPENAME(&foo);

    // ISO/IEC 14882:2011(E) 5.2.8/5
    // The top-level cv-qualifiers of the glvalue expression or the type-id that
    // is the operand of typeid are always ignored.
    TEST_CASE(typeid(int) == typeid(const int));
    TEST_CASE(typeid(int) == typeid(const int &));

    // http://www.zhihu.com/question/35048998
    // TODO

    PAUSE();
    return 0;
}
