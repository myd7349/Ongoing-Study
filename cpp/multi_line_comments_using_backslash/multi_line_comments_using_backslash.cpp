// 2014-06-25T22:51+08:00
#include <iostream>

int main()
{
    // \
    std::cout << "Hello, world!" << std::endl;

    // while, you will see nothing on the screen. \
    Because the "\" at the end of the comment makes the "std::cout..." a \
    multi-line comment.

    return 0;
}

// References:
// [C++ Multi-line comments using backslash](http://stackoverflow.com/questions/7059549/c-multi-line-comments-using-backslash)
// [Backslash newline at end of file warning](http://stackoverflow.com/questions/5708259/backslash-newline-at-end-of-file-warning)
