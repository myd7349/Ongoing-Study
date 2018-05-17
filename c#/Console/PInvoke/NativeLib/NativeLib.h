#pragma once

#ifdef NATIVELIB_EXPORTS
# define NATIVELIB_API __declspec(dllexport)
#else
# define NATIVELIB_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

NATIVELIB_API void Foo();

#ifdef __cplusplus
}
#endif