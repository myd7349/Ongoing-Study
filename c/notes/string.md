2018-09-15T18:56+08:00

https://gitlab.com/tortoisegit/tortoisegit/commit/164212219050568383df88494f9e22b808bcfc08

Use strlcpy instead of strncpy

《Unix 网络编程》 第三版，1.5：
> 值得注意的是，许多网络入侵是由黑客通过发送数据，导致服务器对 sprintf 的调用使其缓冲区溢出而发生的。必须小心使用的函数还有 gets、strcat、strcpy，通常应分别改为调用 fgets、strncat 和 strncpy。更好的替代函数是后来才引入的 strlcat 和 strlcpy，它们确保结果是正确终止的字符串。

https://github.com/sdrsdr/sdrclib

https://github.com/google/glog/blob/ba8a9f6952d04d1403b97df24e6836227751454e/src/demangle.cc#L163

https://stackoverflow.com/questions/51614543/perf-report-shows-this-function-memset-avx2-unaligned-erms-has-overhead-doe

[strdup vs \_strdup](https://stackoverflow.com/questions/7582394/strdup-or-strdup)

《Unix 网络编程》卷一，3.5 字节操纵函数：
> 当源字节串与目标字节串重叠时，bcopy 能够正确处理，但是 memcpy 的操作结果却不可知。这种情形下必须改用 ANSI C 的 memmove 函数。

> 记住 memset 最后两个参数顺序的方法之一是认识到所有 ANSI C 的 memXXX 函数都需要一个长度参数，而且它总是最后一个参数。

[How to use memset function in two dimensional array for initialization of members in C?](https://stackoverflow.com/questions/23039134/how-to-use-memset-function-in-two-dimensional-array-for-initialization-of-member)

[strdup](https://github.com/snowballstem/snowball/pull/136)

[strdup](https://en.cppreference.com/w/c/experimental/dynamic/strdup)

https://github.com/clibs/strdup/blob/master/strdup.c

https://github.com/lattera/glibc/blob/master/string/strdup.c

> ```c
> char *
> __strdup (const char *s)
> {
>   size_t len = strlen (s) + 1;
>   void *new = malloc (len);
> 
>   if (new == NULL)
>     return NULL;
> 
>   return (char *) memcpy (new, s, len);
> }
> ```

[strlen not checking for NULL](https://stackoverflow.com/questions/5796103/strlen-not-checking-for-null)

[strtok](https://github.com/FreeRDP/FreeRDP/blob/d4ae65dbb54683cb08bff4d50f9637c0a325fb9a/winpr/libwinpr/utils/ini.c#L68)

[Getting file extension in C](https://stackoverflow.com/questions/5309471/getting-file-extension-in-c)

[Getting file extension in C language](https://stackoverflow.com/questions/3035225/getting-file-extension-in-c-language)
