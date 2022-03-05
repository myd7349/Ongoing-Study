[malloc is thread-safe but not necessarily reentrant](https://stackoverflow.com/questions/16851948/posix-extended-definition-of-reentrancy-covering-thread-safety)

[override malloc in msvc](https://stackoverflow.com/questions/1316018/globally-override-malloc-in-visual-c)

[Overridable CRT Release/Debug Memory functions (just like malloc)](https://developercommunity.visualstudio.com/idea/403088/overridable-crt-releasedebug-memory-functions-just.html)

[Globally override malloc in visual c++](https://stackoverflow.com/questions/1316018/globally-override-malloc-in-visual-c)

[Visual Studio 2010 library linking order](https://stackoverflow.com/questions/2765403/visual-studio-2010-library-linking-order/12926155#12926155)

[override malloc in glibc](https://www.stev.org/post/chowtooverridemallocfree)

```c
#include <stdio.h>
#include <dlfcn.h>

extern void abort();

void *malloc(int size) {
        void * (*ptr)(int);
        void * handle = (void*) -1;
        ptr = (void *) dlsym(handle, "malloc");
        if (ptr == NULL) {
                printf("Opps\n");
                abort();
        }
        void *alloc = (*ptr)(size);
        printf("Alloc = %p Size: %d\n", alloc, size);
        return alloc;
}

void *realloc(void *alloc, int size) {
        void * (*ptr)(void *, int);
        void * handle = (void*) -1;
        ptr = (void *) dlsym(handle, "malloc");
        if (ptr == NULL) {
                printf("Opps\n");
                abort();
        }
        alloc = (*ptr)(alloc, size);
        printf("Realloc = %p Size: %d\n", alloc, size);
        return alloc;
}

void free(void *alloc) {
        if (alloc == NULL)
                return;
        printf("free %p\n", alloc);
        void * (*ptr)(void *);
        void * handle = (void *) -1;
        ptr = (void *) dlsym(handle, "free");
        if (ptr == NULL)
                abort();

        (*ptr)(alloc);
}
```

[`tcmalloc` overrides `malloc` and `free` via `libc_override_redefine.h`](https://zhuanlan.zhihu.com/p/51432385)

[mi-malloc: Overriding Malloc](https://microsoft.github.io/mimalloc/overrides.html)

[Create a wrapper function for malloc and free in C](https://stackoverflow.com/questions/262439/create-a-wrapper-function-for-malloc-and-free-in-c)

[Hooks for Malloc](https://www.gnu.org/savannah-checkouts/gnu/libc/manual/html_node/Hooks-for-Malloc.html)

[tcmalloc: how can I get my malloc calls overridden when compiling statically?](https://stackoverflow.com/questions/1553435/tcmalloc-how-can-i-get-my-malloc-calls-overridden-when-compiling-statically)

[Problem in overriding malloc](https://stackoverflow.com/questions/1094532/problem-in-overriding-malloc)

[What is the LD_PRELOAD trick?](https://stackoverflow.com/questions/426230/what-is-the-ld-preload-trick)

[some standard libraries have a mutex lock in rand() that can dramatically hurt performance when run across multiple threads.](https://github.com/google/marl/commit/59068ee4cf1f5ff5e691ff010c8d83b5f862c4fa)

- https://github.com/google/marl/issues/17
- [Using stdlib's rand() from multiple threads](https://stackoverflow.com/questions/6161322/using-stdlibs-rand-from-multiple-threads)

max and min:

```c
// https://github.com/Tencent/ncnn/blob/master/src/simpleocv.h
#if defined(_MSC_VER) || defined(__GNUC__)
#pragma push_macro("min")
#pragma push_macro("max")
#undef min
#undef max
#endif

// ...

#if defined(_MSC_VER) || defined(__GNUC__)
#pragma pop_macro("min")
#pragma pop_macro("max")
#endif
```

https://github.com/curl/curl/blob/e28628ffc22f3516a6560fbd6d8a19c50fa74306/lib/strdup.c#L114-L121

> ```c
> /***************************************************************************
>  *
>  * Curl_saferealloc(ptr, size)
>  *
>  * Does a normal realloc(), but will free the data pointer if the realloc
>  * fails. If 'size' is non-zero, it will free the data and return a failure.
>  *
>  * This convenience function is provided and used to help us avoid a common
>  * mistake pattern when we could pass in a zero, catch the NULL return and end
>  * up free'ing the memory twice.
>  *
>  * Returns the new pointer or NULL on failure.
>  *
>  ***************************************************************************/
> void *Curl_saferealloc(void *ptr, size_t size)
> {
>   void *datap = realloc(ptr, size);
>   if(size && !datap)
>     /* only free 'ptr' if size was non-zero */
>     free(ptr);
>   return datap;
> }
> ```

https://en.cppreference.com/w/c/memory/realloc

> If there is not enough memory, the old memory block is not freed and null pointer is returned.

[Is it bad practice to allocate memory in a DLL and give a pointer to it to a client app?](https://stackoverflow.com/questions/13625388/is-it-bad-practice-to-allocate-memory-in-a-dll-and-give-a-pointer-to-it-to-a-cli)

> **Avoids mismatching the allocator and deallocator.** As mentioned in [Aesthete's answer](https://stackoverflow.com/a/13625555/179715), if the DLL allocates a pointer and returns it, the caller *must* call the corresponding deallocator to free it. This is not necessarily
>  trivial: the DLL might be statically linked against one version of, 
> say, `malloc`/`free` while the `.exe` is linked against a different version of `malloc`/`free`. (For example, the DLL could be using release versions while the `.exe` is using specialized debug versions.)

calloc

- [Is calloc(4, 6) the same as calloc(6, 4)?](https://stackoverflow.com/questions/501839/is-calloc4-6-the-same-as-calloc6-4)

- [is the order of parameters to calloc() important?](https://stackoverflow.com/questions/48815191/is-the-order-of-parameters-to-calloc-important)
