#ifndef FOO_H_
#define FOO_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "foo_export.h"


FOO_API int foo();
FOO_API const char *bar();

#ifdef __cplusplus
}
#endif

#endif


// References:
// https://gcc.gnu.org/wiki/Visibility
// https://stackoverflow.com/questions/22285240/mingw-use-declspecdllexport-or-attribute-visibilitydefault
// https://github.com/raysan5/raylib/pull/789#issuecomment-482923913
