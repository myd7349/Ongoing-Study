#if defined(FOO_SHARED)
#  if defined(FOO_BUILD)
#    if defined(_WIN32)
#      define FOO_API __declspec(dllexport)
#    elif defined(__ELF__)
#      define FOO_API __attribute__ ((visibility ("default")))
#    else
#      define FOO_API
#    endif
#  else
#    if defined(_WIN32)
#      define FOO_API __declspec(dllimport)
#    else
#      define FOO_API
#    endif
#  endif
#else
#  define FOO_API
#endif

FOO_API void Foo(void);
