// 2014-12-08T10:27+08:00
// Do test on several obscure C++ features introduced here:
// http://madebyevan.com/obscure-cpp-features/
#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <type_traits>

#include "../uniform_typename/uniform_typename.h"

#define JUST_GO() \
    do { \
        auto funcNameLen = std::strlen(__func__); \
        if (funcNameLen < 79 - 2) { \
            auto paddingCnt = (79 - 2 - funcNameLen) / 2; \
            auto padding = std::string(paddingCnt, '-'); \
            auto output = padding + ' ' + __func__ + ' ' + padding; \
            std::cout << output << (output.length() == 78 ? "-\n" : "\n"); \
        } else { \
            std::cout << __func__ << std::endl; \
        } \
    } while (0)

// 0. What square brackets really mean
void what_square_brackets_really_mean()
{
    JUST_GO();

    int arr[] { 0, 1, 2, 3 };

    // arr[3] is just short for *(arr + 3)
    assert(arr[3] == *(arr + 3));
    // 3[arr] is also OK!
    assert(arr[3] == 3[arr]);
}

// 1. Most vexing parse
// TODO: standard
void most_vexing_parse()
{
    JUST_GO();

    int (x) = 0; // really funny

    assert(0 == x);

    // ------------------------------------------------------------------------------
    std::string foo(std::string());
    int bar(int(x));

    assert(std::is_function<decltype(foo)>::value);
    assert(std::is_function<decltype(bar)>::value);

    std::cout << TYPE_NAME(foo) << std::endl;
    std::cout << TYPE_NAME(bar) << std::endl;

    // ------------------------------------------------------------------------------
    std::string foo2((std::string()));
    int bar2((int(x)));

    assert(!std::is_function<decltype(foo2)>::value);
    assert(!std::is_function<decltype(bar2)>::value);

    std::cout << TYPE_NAME(foo2) << std::endl;
    std::cout << TYPE_NAME(bar2) << std::endl;
}

// 2. Alternate operator tokens
void alternate_operator_tokens()
{
    JUST_GO();

}

// 3.
class MyClass
{
public:
    MyClass()
    {
        std::cout << __func__ << std::endl;
    }

    ~MyClass()
    {
        std::cout << __func__ << std::endl;
    }
};

/* MFC CArray
template<class TYPE, class ARG_TYPE>
CArray<TYPE, ARG_TYPE>::~CArray()
{
	ASSERT_VALID(this);

	if (m_pData != NULL)
	{
		for( int i = 0; i < m_nSize; i++ )
			(m_pData + i)->~TYPE();
		delete[] (BYTE*)m_pData;
	}
}
*/

void skip_destructor()
{
    JUST_GO();

    MyClass *obj1 = new MyClass;
    delete obj1;

    MyClass *obj3 = new MyClass;
    obj3->~MyClass();
    delete (unsigned char *)obj3;

    MyClass *obj2 = new MyClass;
    delete (unsigned char *)obj2;
}

int main()
{
    what_square_brackets_really_mean();

    most_vexing_parse();

    alternate_operator_tokens();

    skip_destructor();

    return 0;
}
