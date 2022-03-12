https://github.com/google/glog/blob/ba8a9f6952d04d1403b97df24e6836227751454e/src/symbolize.cc#L136

https://en.cppreference.com/w/cpp/error/errno_macros

https://en.cppreference.com/w/cpp/error/system_category

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
