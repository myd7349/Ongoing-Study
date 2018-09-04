#ifdef _WIN32

#ifndef USING_UNICODE
#define USING_UNICODE (1)
#endif

#if USING_UNICODE
#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif
#endif

#include <tchar.h>

#elif defined(__linux__)

#define _tmain main
#define _TCHAR char
#define _T(x) x
#define _istalpha isalpha
#define _stprintf sprintf
#define _tscanf scanf
#define _fgetts fgets
#define _tprintf printf
#define _ftprintf fprintf
#define _tcstol strtol
#define _tcscmp strcmp
#define _tcscpy strcpy
#define _tcsncpy strncpy
#define _tcslen strlen
#define _tcsupr strupr
#define _tcschr strchr
#define _tcsrchr strrchr

#else

#error Unsupported platform!

#endif