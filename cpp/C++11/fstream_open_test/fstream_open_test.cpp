// 2014-08-09T15:30+08:00
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

int main()
{
    std::string filename = "test.log";

    std::ofstream out;

    // In C++11,
    // void ofstream::open (const string& ,  ios_base::openmode);
    // and
    // explicit ofstream::ofstream (const string&, ios_base::openmode);
    // is added.
    // So, here filename.c_str() is not needed any more.
    out.open(filename);

    if (out) {
        out << "Hello, world!\n";
        out.close();
    }

    std::remove(filename.c_str());

    return 0;
}
