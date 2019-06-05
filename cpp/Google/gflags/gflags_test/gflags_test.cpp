#include <iostream>

#include <gflags/gflags.h>

DEFINE_string(say_hello, "Hello, world!", "Say hello");


int main(int argc, char *argv[])
{
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    std::cout << FLAGS_say_hello << std::endl;

    return 0;
}
