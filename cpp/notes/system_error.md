1. system_category

https://en.cppreference.com/w/cpp/error/system_category

C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.32.31326\include\filesystem

```cpp
_NODISCARD inline error_code _Make_ec(__std_win_error _Errno) noexcept { // make an error_code
    return {static_cast<int>(_Errno), _STD system_category()};
}

[[noreturn]] inline void _Throw_system_error_from_std_win_error(const __std_win_error _Errno) {
    _THROW(system_error{_Make_ec(_Errno)});
}
```

2.

```cpp
#include <cstring>
#include <iostream>
#include <system_error>
 
int main()
{
    std::error_condition econd = std::system_category().default_error_condition(EAGAIN);
    std::cout << "Category: " << econd.category().name() << '\n'
              << "Value: " << econd.value() << '\n'
              << "Message: " << econd.message() << '\n';
    std::cout << std::strerror(EAGAIN) << '\n';
    return 0;
}

// Output:
/*
Category: generic
Value: 11
Message: Resource temporarily unavailable
Resource temporarily unavailable
*/
```
