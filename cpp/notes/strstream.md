https://en.cppreference.com/w/cpp/io/strstream

https://en.cppreference.com/w/cpp/io/strstream/freeze

https://en.cppreference.com/w/cpp/io/manip/ends

> ```cpp
> #include <cstdio>
> #include <strstream>
> int main()
> {
>     std::ostrstream oss;
>     oss << "Sample text: " << 42 << std::ends;
>     std::printf("%s\n", oss.str());
>     oss.freeze(false); // enable memory deallocation
> }
> ```
