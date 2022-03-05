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

[PyStand/PyStand.cpp at 164a7b929d1d3c35f299da2669dc112775e724d7 · skywind3000/PyStand · GitHub](https://github.com/skywind3000/PyStand/blob/164a7b929d1d3c35f299da2669dc112775e724d7/PyStand.cpp#L68-L77)

> ```cpp
> std::wstring PyStand::Ansi2Unicode(const char *text)
> {
>     int require = (int)strlen(text) * 2 + 10;
>     std::wstring wide;
>     wide.resize(require + 2);
>     MultiByteToWideChar(CP_ACP, 0, text, -1, &wide[0], require);
>     int size = wcslen(wide.c_str());
>     wide.resize(size);
>     return wide;
> }
> ```

[Difference between strlen(str.c_str()) and str.length() for std::string](https://stackoverflow.com/questions/29302073/difference-between-strlenstr-c-str-and-str-length-for-stdstring)

> As an implicit understanding, I always thought that every implementation of `std::string` necessarily must satisfy `strlen(str.c_str()) == str.length()` for every string `str`.

and an answer:

> Your understanding is incorrect. Sort of.
> 
> `std::string` may contain `char`s with the value `'\0'`; when you extract a C-string, you have no way of knowing how long it is other than to scan for `\0`s, which by necessity cannot account for "binary data".
> 
> This is a limitation of `strlen`, and one that `std::string` "fixes" by actually remembering this metadata as a count of `char`s that it knows are encapsulated.
> 
> The standard doesn't really need to "say" anything about it, except that `std::string::length` gives you the string length, no matter what the value of the `char`s you inserted into the string, and that is it not prohibited to insert a `'\0'`. By contrast, `strlen` is defined to tell you how many `char`s exist up to the next `\0`, which is a fundamentally different definition.
> 
> There is no explicit wording about this, because there does not need 
> to be. If there were an exception to the very simple rules ("there is a 
> string; it has `char`s; it can tell you how many `char`s it has") then *that* would be stated explicitly… and it's not.

[Does std::string have a null terminator?](https://stackoverflow.com/questions/11752705/does-stdstring-have-a-null-terminator)

> No, but if you say `temp.c_str()` a null terminator will be included in the return from this method.

> Not in C++03, and it's not even guaranteed before C++11 that in a C++
>  std::string is continuous in memory. Only C strings (char arrays which 
> are intended for storing strings) had the null terminator.
> 
> In C++11 and later, `mystring.c_str()` is equivalent to `mystring.data()` is equivalent to `&mystring[0]`, and `mystring[mystring.size()]` is guaranteed to be `'\0'`.
> 
> In C++17 and later, `mystring.data()` also provides an overload that returns a non-const pointer to the string's contents, while `mystring.c_str()` only provides a `const`-qualified pointer.

[What does c_str() method from string class returns?](https://stackoverflow.com/questions/17402980/what-does-c-str-method-from-string-class-returns)

> In *C++11* standard it's explicitly stated that `.c_str()` (as well as newer `.data()`) shall return pointer to the internal buffer which is used by `std::string`.
> 
> Any modification of the std::string after obtaining the pointer via `.c_str()` *may* result in said `char *` returned to became invalid (that is - if `std::string` internally had to reallocate the space).
> 
> In previous C++ standards implementation is allowed to return 
> anything. But as standard do not require user to deallocate the result, 
> I've never seen any implementation returning anything newly allocated. 
> At least GNU gcc's and MSVC++'s STL string are internally 
> zero-terminated char arrays, which are returned by `c_str()`.

> ```cpp
> std::string s = "hello";
> s[5] == '\0'; // Assertion failure in VS2010.
> ```