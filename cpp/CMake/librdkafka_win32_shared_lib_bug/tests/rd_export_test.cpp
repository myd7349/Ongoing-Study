#include <cstdio>
#include <cstdlib>
#include <string>

#include <foo/foo.h>


int main(void)
{
#ifdef _MSC_VER
# ifdef LIBRDKAFKA_STATICLIB
    return 0;
# else
    std::printf("%s\n", FOO_STR(RD_EXPORT));
    int expected = std::string(FOO_STR(RD_EXPORT)) == "__declspec(dllimport)";
    std::printf("As expected? %d\n", expected);
    return expected ? 0 : EXIT_FAILURE;
# endif
#else
    return 0;
#endif
}
