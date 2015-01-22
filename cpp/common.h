// 2015-01-22T16:59+08:00

// Some frequently used stuffs.

#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#ifdef _MSC_VER
# ifdef NDEBUG
#  define PAUSE() (__noop)
# else
#  include <cstdlib>
#  define PAUSE() std::system("pause")
# endif
#else
# define PAUSE() ((void)0)
#endif

#include <iostream>
#define RETURN_ON_FAILURE_MSG(msg) std::cerr << msg << ": " << e.what() << '\n'; PAUSE(); return EXIT_FAILURE
#define RETURN_ON_FAILURE() std::cerr << e.what() << '\n'; PAUSE(); return EXIT_FAILURE

#endif