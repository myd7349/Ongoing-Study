https://stackoverflow.com/questions/3004095/division-by-zero-undefined-behavior-or-implementation-defined-in-c-and-or-c

https://stackoverflow.com/questions/4745311/c-division-by-0

>For IEEE floats, division of a finite nonzero float by 0 is well-defined and results in +infinity (if the value was >zero) or -infinity (if the value was less than zero). The result of 0.0/0.0 is NaN. If you use integers, the behaviour is undefined.

https://stackoverflow.com/questions/42926763/the-behaviour-of-floating-point-division-by-zero

https://github.com/protocolbuffers/upb/blob/00e739648d816fae3972c9d51fef24940cf50539/upb/json/printer.c#L184

https://stackoverflow.com/questions/6235847/how-to-generate-nan-infinity-and-infinity-in-ansi-c

https://stackoverflow.com/questions/2538339/infinity-in-msvc

https://stackoverflow.com/questions/40181267/msvc-equivalent-to-gccs-fno-finite-math-only

json-c/math_compact.h

```c
#ifndef HAVE_DECL_ISNAN
# ifdef HAVE_DECL__ISNAN
#include <float.h>
#define isnan(x) _isnan(x)
# endif
#endif

#ifndef HAVE_DECL_ISINF
# ifdef HAVE_DECL__FINITE
#include <float.h>
#define isinf(x) (!_finite(x))
# endif
#endif
```

https://www.codeproject.com/Tips/676287/C-and-Cplusplus-Use-isnan-to-Test-for-NaN

https://bugs.mysql.com/bug.php?id=28240

https://www.gnu.org/software/libc/manual/html_node/Infinity-and-NaN.html

https://github.com/thejefflarson/quadtree/pull/3/files

https://github.com/lpsinger/gst-plugins-cairovis/pull/1/files

```c
#if defined(_MSC_VER)
__inline const double log2( double n ) { return log( n ) / log( 2 ); }
__inline const int isfinite( double n) { return n != HUGE_VAL; }
#define INFINITY G_MAXDOUBLE
#endif /* _MSC_VER */
```

https://github.com/winlibs/glib/blob/master/glib/glibconfig.h.win32

https://devblogs.microsoft.com/cppblog/c99-library-support-in-visual-studio-2013/

https://stackoverflow.com/questions/20016600/negative-infinity

https://www.linuxquestions.org/questions/programming-9/c-language-inf-and-nan-437323/

```
+NAN float: 7fc00000
-NAN float: 7fc00000
+NAN double: 7ff8000000000000
-NAN double: 7ff8000000000000

+INF float: 7f800000
-INF float: 7f800000
+INF double: 7ff0000000000000
-INF double: 7ff0000000000000
```

https://docs.microsoft.com/en-us/cpp/porting/visual-cpp-change-history-2003-2015?view=vs-2019

https://github.com/jlblancoc/suitesparse-metis-for-windows/issues/19

https://github.com/jlblancoc/suitesparse-metis-for-windows/pull/22/files

https://www.gnu.org/software/libc/manual/html_node/Floating-Point-Classes.html#Floating-Point-Classes

https://www.oreilly.com/library/view/c-in-a/0596006977/re122.html

https://github.com/abolz/Drachennest/blob/master/src/schubfach_64.cc

[Questions about the implemenation of f64_bin_to_dec](https://github.com/ibireme/yyjson/issues/54)

[fma](https://en.cppreference.com/w/c/numeric/math/fma)

https://github.com/mreineck/pocketfft/blob/master/pocketfft.c

```c
// adapted from https://stackoverflow.com/questions/42792939/
// CAUTION: this function only works for arguments in the range [-0.25; 0.25]!
static void my_sincosm1pi (double a, double *restrict res)
  {
  double s = a * a;
  /* Approximate cos(pi*x)-1 for x in [-0.25,0.25] */
  double r =     -1.0369917389758117e-4;
  r = fma (r, s,  1.9294935641298806e-3);
  r = fma (r, s, -2.5806887942825395e-2);
  r = fma (r, s,  2.3533063028328211e-1);
  r = fma (r, s, -1.3352627688538006e+0);
  r = fma (r, s,  4.0587121264167623e+0);
  r = fma (r, s, -4.9348022005446790e+0);
  double c = r*s;
  /* Approximate sin(pi*x) for x in [-0.25,0.25] */
  r =             4.6151442520157035e-4;
  r = fma (r, s, -7.3700183130883555e-3);
  r = fma (r, s,  8.2145868949323936e-2);
  r = fma (r, s, -5.9926452893214921e-1);
  r = fma (r, s,  2.5501640398732688e+0);
  r = fma (r, s, -5.1677127800499516e+0);
  s = s * a;
  r = r * s;
  s = fma (a, 3.1415926535897931e+0, r);
  res[0] = c;
  res[1] = s;
  }
```
