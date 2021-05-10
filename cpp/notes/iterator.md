[Avoid inheritance from std::iterator](https://github.com/Tencent/rapidjson/pull/1137)

[Testing whether an iterator points to the last item?](https://stackoverflow.com/questions/3516196/testing-whether-an-iterator-points-to-the-last-item)

```cpp
if (it == std::prev(lst.end())) {
}
```

```cpp
#include <iterator>

// Note: Use std::prev, std::next instead.
template <typename InputIterator, typename Distance>
InputIterator Advance(InputIterator it, Distance offset)
{
    InputIterator targetIterator = it;
    std::advance(targetIterator, offset);
    return targetIterator;
}
```

[Trouble with garbage chars in visual c++ file reading](https://stackoverflow.com/questions/19482938/trouble-with-garbage-chars-in-visual-c-file-reading)

```c++
#include <fstream>
#include <iostream>
#include <iterator>

void readfile(const char *inputfile) {
    std::ifstream is(inputfile);
    std::string buf(std::istreambuf_iterator<char>(is), {});
    std::cout << buf << std::endl;
}

int main()
{
    readfile("main.cpp");
}
```

and before C++11:

```cpp
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

void readfile(const char *inputfile) {
    std::ifstream is(inputfile);
    std::istreambuf_iterator<char> f(is), l;
    std::vector<char> buf(f, l);

    std::cout.write(buf.data(), buf.size());
}

int main()
{
    readfile("main.cpp");
}
```

