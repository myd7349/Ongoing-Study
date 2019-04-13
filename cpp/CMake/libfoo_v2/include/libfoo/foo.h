#ifndef FOO_H_
#define FOO_H_

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(_WIN32) // _MSC_VER
#  ifdef FOO_STATIC_LIB
#    define FOO_API
#  elif defined(FOO_SHARED_LIB)
#    if defined(FOO_EXPORTS)
#      define FOO_API __declspec(dllexport)
#    else
#      define FOO_API __declspec(dllimport)
#    endif
#  endif
#else
#  define FOO_API
#endif


FOO_API int foo();
FOO_API const char *bar();

#ifdef __cplusplus
}
#endif

#endif
