// 2014-07-21T18:02+08:00
#include <iostream>

// ISO IEC 14882 2011 (C++11) 7.2,
// Enumeration declarations

struct {
    enum {
        EA,
        EB,
        EC,
    } type;
    void *data;
} data_chunk;

// http://en.cppreference.com/w/cpp/language/enum
struct DataChunk {
    enum class : short { // scoped enumeration
        EA2, // scoped enumerator
        EB2,
        EC2,
    };
    enum { // unscoped enumeration
        ED, // unscoped enumerator
        EE,
        EF,
    } type;
    void *data;
};

int main()
{
    // error: 'EA' was not declared in this scope
    // std::cout << EA << std::endl;

    // The name of an unscoped enumeration may be omitted:
    // such declaration only introduces the enumerators
    // into the enclosing scope.
    //
    // When an unscoped enumeration is a class member,
    // its enumerators may be accessed using class member
    // access operators . and ->:
    std::cout << data_chunk.EA << std::endl;

    std::cout << DataChunk::ED << std::endl;
    return 0;
}
