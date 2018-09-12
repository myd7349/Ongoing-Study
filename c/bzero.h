#if defined(_WIN32)
# include <string.h>
# define bzero(s, n) memset((s), 0, (n))
#elif defined(__linux__)
# include <strings.h> // for bzero
#else
# error Unsupported platform!
#endif


// References:
// http://man7.org/linux/man-pages/man3/bzero.3.html
