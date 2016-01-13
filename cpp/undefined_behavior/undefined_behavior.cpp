// 2015-05-30T21:49+08:00
// List of undefined behaviors in C++.

// 1. dereferencing a null pointer.
//    An example from Effective C++ 3E/Introduction/Terminology
//        int *p = NULL;
//        std::cout << *p;
//

// 2. referring an invalid array index
//    An example from Effective C++ 3E/Introduction/Terminology
//        char name[] = "Darla";
//        char c = name[10];

// 2015-08-09T23:02+08:00
// 3. Refer to an uninitialized built-in object is undefined.
// 4. The relative order of initialization of non-local static objects defined
//    in different translation units is undefined.
//    An example from Effective C++ 3E/Item 04
//        class FileSystem {...

// 2016-01-13T09:58+08:00
// Deprecated. It's meaningless.

int main()
{
    return 0;
}
