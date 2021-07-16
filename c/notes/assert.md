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

