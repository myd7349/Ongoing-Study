#if defined(BAR_SHARED)
#  if defined(BAR_BUILD)
#    if defined(_WIN32)
#      define BAR_API __declspec(dllexport)
#    elif defined(__ELF__)
#      define BAR_API __attribute__ ((visibility ("default")))
#    else
#      define BAR_API
#    endif
#  else
#    if defined(_WIN32)
#      define BAR_API __declspec(dllimport)
#    else
#      define BAR_API
#    endif
#  endif
#else
#  define BAR_API
#endif

BAR_API void Bar(void);
