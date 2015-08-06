#ifndef ZEN_H_
#define ZEN_H_

static int Zen_of_life = 42;
extern int hah;

// In C++, a name of file scope that is explicitly declared const, and not explicitly declared extern, has internal linkage,
// while in C it would have external linkage.
#define TEST_FILE_SCOPE_CONSTANT_LINKAGE (0)

#if TEST_FILE_SCOPE_CONSTANT_LINKAGE
const int Duang = 998;
#endif

#endif // ZEN_H_

// References:
// [Where to declare/define class scope constants in C++?](http://stackoverflow.com/questions/2043493/where-to-declare-define-class-scope-constants-in-c)
// [Why does const imply internal linkage in C++, when it doesn't in C?](http://stackoverflow.com/questions/998425/why-does-const-imply-internal-linkage-in-c-when-it-doesnt-in-c)
