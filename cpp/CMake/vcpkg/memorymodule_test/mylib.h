#pragma once

#ifdef _WIN32
#define MYLIB_API __declspec(dllexport)
#else
#define MYLIB_API
#endif

MYLIB_API void Foo(const char *name);
