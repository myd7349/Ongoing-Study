https://en.cppreference.com/w/cpp/language/new

[C++ new 動態記憶體配置用法與範例 | ShengYu Talk](https://shengyu7697.github.io/cpp-new-delete/)

https://en.cppreference.com/w/cpp/memory/new/nothrow

> ```cpp
> #include <iostream>
> #include <new>
> 
> int main()
> {
>     try {
>         while (true) {
>             new int[100000000ul];   // throwing overload
>         }
>     } catch (const std::bad_alloc& e) {
>         std::cout << e.what() << '\n';
>     }
> 
>     while (true) {
>         int* p = new(std::nothrow) int[100000000ul]; // non-throwing overload
>         if (p == nullptr) {
>             std::cout << "Allocation returned nullptr\n";
>             break;
>         }
>     }
> }
> ```
