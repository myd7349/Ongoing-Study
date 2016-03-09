// 2016=03-09T13:20+08:00
#include <complex.h>
#include <stdio.h>

#include "../../common.h"

int main()
{
#if defined(_MSC_VER) && _MSC_VER <= 1900 // VS2015
    //_Dcomplex x = 5.2;
    //_Dcomplex y = 5.0 * I;
    //_Dcomplex z = 5.2 + 5.0 * I;
    _Fcomplex x = I;
    _Dcomplex y = _DCOMPLEX_(5.0, 1);
#elif defined(__GNUC__)
    float _Complex x = 5.2;
    double complex y = 5.0 * I;
    double complex z = 5.2 + 5.0 * I;

    printf("x: %f + %fi\n", crealf(x), cimagf(x));
    printf("y: %f + %fi\n", creal(y), cimag(y));
    printf("z: %f + %fi\n", __real__ z, __imag__ z);
#endif

    PAUSE();
    return 0;
}

// References:
// [MSVC 2015 complex.h's '_Complex_I' macro does not conform to the standard](https://connect.microsoft.com/VisualStudio/feedback/details/1551173/msvc-2015-complex-hs-complex-i-macro-does-not-conform-to-the-standard)
// [libffi tip Windows build bustage](https://github.com/atgreen/libffi/issues/138)
// [Compiling the GTK+ (and Clutter) stack using Visual C++ 2008 and later](https://wiki.gnome.org/Projects/GTK+/Win32/MSVCCompilationOfGTKStack)
// [Complex Numbers](https://gcc.gnu.org/onlinedocs/gcc-3.1/gcc/Complex.html)
