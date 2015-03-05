// 2014-10-06T22:14+08:00
// http://www.zhihu.com/question/25746754
#include <iostream>
#include <map>

int main()
{
    typedef struct ZkStruct {
        int  x;
        char s[20];
    } ZkStruct;

    // non C++ 11:
    // error: template argument for 'template<class _T1, class _T2> struct std::pair'
    // uses local type 'main()::ZkStruct'
    // ISO C++ 98/03 14.3.1.2
    // A local type, a type with no linkage, an unnamed type or a type compounded
    // from any of these types shall not be used as a template-argument for a template
    // type-parameter.
    // ISO C++ 0x/11:
    // http://stackoverflow.com/questions/5751977/local-type-as-template-arguments-in-c
    std::map<int, ZkStruct> zkmap;

    return 0;
}
