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

