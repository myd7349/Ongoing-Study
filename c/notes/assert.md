[C++ assert implementation in assert.h](https://stackoverflow.com/questions/9701229/c-assert-implementation-in-assert-h)

https://github.com/json-c/json-c/pull/501/files

[Unreachable](https://github.com/simdjson/simdjson/blob/06643fc9f5f1019c49dc4564cf56a8c47010ad15/singleheader/simdjson.h#L253-L259)

> ```cpp
> #ifdef SIMDJSON_VISUAL_STUDIO
> #define SIMDJSON_UNREACHABLE() __assume(0)
> #define SIMDJSON_ASSUME(COND) __assume(COND)
> #else
> #define SIMDJSON_UNREACHABLE() __builtin_unreachable();
> #define SIMDJSON_ASSUME(COND) do { if (!(COND)) __builtin_unreachable(); } while (0)
> #endif
> ```

[c - assert() with message - Stack Overflow](https://stackoverflow.com/questions/5867834/assert-with-message)

> ```c
> assert(condition && "message");
> ```

https://github.com/ibireme/yyjson/blob/master/test/util/yy_test_utils.h

static_assert

https://github.com/sccn/liblsl/blame/master/include/lsl/common.h

```c
// Abort compilation if lsl_channel_format_t isn't exactly 4 bytes wide
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
_Static_assert(sizeof(lsl_channel_format_t) == 4, "lsl_channel_format_t size breaks the LSL ABI");
#elif defined(__cplusplus) && __cplusplus >= 201103L
static_assert (sizeof(lsl_channel_format_t) == 4, "lsl_channel_format_t size breaks the LSL ABI");
#elif !defined(LIBLSL_FFI)
static char _lsl_channel_format_size_check[1 - 2*!(sizeof(lsl_channel_format_t)==4)];
#endif
```
