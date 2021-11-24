[std::string to char*](https://stackoverflow.com/questions/7352099/stdstring-to-char)

[Why does std::string(“\x00”) report length of 0?](https://stackoverflow.com/questions/48255276/why-does-stdstring-x00-report-length-of-0)

> std::string("\x00") -> length == 0
>
> std::string(1, '\0') -> length == 1
>
> std::string{ '\0' } -> length == 1

[write yyjson to file issue](https://github.com/ibireme/yyjson/issues/50)

> The input of these functions should be null-terminated strings,
>  you should use `string.c_str()` instead of `string.data()`.

[string c_str() vs. data()](https://stackoverflow.com/questions/194634/string-c-str-vs-data)

> The documentation is correct. Use [`c_str()`](http://en.cppreference.com/w/cpp/string/basic_string/c_str) if you want a null terminated string.
>
> If the implementers happend to implement [`data()`](http://en.cppreference.com/w/cpp/string/basic_string/data) in terms of `c_str()` you don't have to worry, still use `data()` if you don't need the string to be null terminated, in some implementation it may turn out to perform better than c_str().
>
> strings don't necessarily have to be composed of character data, they could be composed with elements of any type. In those cases `data()` is more meaningful. `c_str()` in my opinion is only really useful when the elements of your string are character based.
>
> *Extra*: In C++11 onwards, both functions are required to be the same. i.e. `data` is now required to be null-terminated.  According to [cppreference](http://en.cppreference.com/w/cpp/string/basic_string/data): "The returned array is null-terminated, that is, data() and c_str() perform the same function."

[Are wchar_t and char16_t the same thing on Windows?](https://stackoverflow.com/questions/53293159/are-wchar-t-and-char16-t-the-same-thing-on-windows)