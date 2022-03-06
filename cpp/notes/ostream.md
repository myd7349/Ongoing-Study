##### std::endl

[embed cmd in win32 application and text not selectable](https://stackoverflow.com/questions/50043663/embed-cmd-in-win32-application-and-text-not-selectable)

> ```cpp
> //this is for std::endl
> my_stream& operator<<(std::wostream& (*func)(std::wostream&))
> {
>     oss.str(L"");
>     oss << func;
>     append_to_richedit(oss.str().c_str());
>     return *this;
> }
> ```

https://en.cppreference.com/w/cpp/io/manip/endl

["std::endl" vs "\n"](https://stackoverflow.com/questions/213907/stdendl-vs-n)

##### std::ends

[What use is there for 'ends' these days?](https://stackoverflow.com/questions/2338377/what-use-is-there-for-ends-these-days)

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
  
