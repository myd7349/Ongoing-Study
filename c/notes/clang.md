https://compiler-explorer.com/z/jxvdj8Kv4

> ```c
> #include <cstdio>
> 
> int main() {
>     FILE f;
>     __builtin_dump_struct(&f, &printf);
>     return sizeof(f);
> }
> ```


