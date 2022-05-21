// 2015-03-11T13:39+08:00
// [Copy a file in an sane, safe and efficient way](http://stackoverflow.com/questions/10195343/copy-a-file-in-an-sane-safe-and-efficient-way)
#include <fstream>
#include <iostream>

#include "../common.h"

int main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cerr << "Usage: " << GetProgName(argv[0]) << " srcfile destfile\n";
        return EXIT_FAILURE;
    }

    std::ifstream src_file(argv[1], std::ios::binary);
    if (!src_file) {
        std::cerr << "Opening source file \"" << argv[1] << "\" failed!\n";
        return EXIT_FAILURE;
    }

    std::ofstream dest_file(argv[2], std::ios::binary);
    if (!dest_file) {
        std::cerr << "Opening destination file \"" << argv[2] << "\" failed!\n";
        return EXIT_FAILURE;
    }

    dest_file << src_file.rdbuf();

    return 0;
}

/*
https://github.com/hoffstadt/DearPyGui/blob/v1.5.0/DearSandbox/main.cpp

```cpp
auto ss = std::ostringstream{};
std::ifstream input_file("../../DearSandbox/sandbox.py");
ss << input_file.rdbuf();
auto content = ss.str();
```
*/
