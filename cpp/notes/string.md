[std::string to char*](https://stackoverflow.com/questions/7352099/stdstring-to-char)

[Why does std::string(“\x00”) report length of 0?](https://stackoverflow.com/questions/48255276/why-does-stdstring-x00-report-length-of-0)

> std::string("\x00") -> length == 0
>
> std::string(1, '\0') -> length == 1
>
> std::string{ '\0' } -> length == 1