#include <cstdio>
#include <string>

#include "captured_stream.hpp"
#include "mini_gtest.hpp"


TEST(stdio, fprintf)
{
    CaptureTestStderr();
    fprintf(stderr, "%.2lf", 3.1415926);
    const std::string output = GetCapturedTestStderr();

    EXPECT_STREQ(output.c_str(), "3.14");
}


int main()
{
    // Make sure stderr is not buffered as stderr seems to be buffered
    // on recent windows.
    std::setbuf(stderr, NULL);
    CaptureTestStderr();

    std::cerr << "Unknown error!\n";
    std::cout << "Hello, world!\n";

    const std::string early_stderr = GetCapturedTestStderr();
    std::cout << early_stderr;

    RUN_ALL_TESTS();

    return 0;
}
