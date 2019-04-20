#ifndef RAYLIB_H_
#define RAYLIB_H_

#if defined(_WIN32) && defined(BUILD_LIBTYPE_SHARED)
    #define RLAPI __declspec(dllexport)         // We are building raylib as a Win32 shared library (.dll)
#elif defined(_WIN32) && defined(USE_LIBTYPE_SHARED)
    #define RLAPI __declspec(dllimport)         // We are using raylib as a Win32 shared library (.dll)
#else
    #define RLAPI   // We are building or using raylib as a static library (or Linux shared library)
#endif

RLAPI void rlHello(void);

#endif


// References:
// https://github.com/raysan5/raylib/pull/789#issuecomment-482923913
