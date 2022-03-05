#include "Error.h"

#include <cerrno>
#include <cstring>
#include <sstream>

#include "Platform.h"

#if defined(_WIN32) || defined(__MINGW32__) || defined(__MINGW64__) || \
    defined(__CYGWIN__)
#include <windows.h>
#endif


inline std::string Strerror(int error)
{
#if defined(_MSC_VER)
    // MSVC doesn't have strerrorlen_s.
    char buffer[256];
    errno_t result = strerror_s(buffer, ARRAYSIZE(buffer), error);
    if (result == 0)
        return buffer;
    else
        return "";
#else
    return std::strerror(error);
#endif
}



#if defined(_WIN32) || defined(__MINGW32__) || defined(__MINGW64__) || \
    defined(__CYGWIN__)
inline std::string WinErrorToString(int error)
{
    char *buffer = NULL;
    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
        NULL, error,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (PSTR)&buffer, 0, NULL);

    std::string message = buffer;
    LocalFree(buffer);

    return message;
}
#endif


std::string ReportError(const char *prompt)
{
    std::ostringstream oss;

    if (prompt != nullptr)
        oss << prompt;

    if (prompt != nullptr)
        oss << "\n    > ";

    oss << "errno: " << errno
        << ", strerror(" << errno << "): " << Strerror(errno)
        << std::endl;

#if 0
    if (gaiError)
    {
        if (prompt != nullptr)
            oss << "    > ";

#if defined(_WIN32)
        oss << "gai_strerror(" << error << "): " << gai_strerrorA(error)
            << std::endl;
#else
        oss << "gai_strerror(" << error << "): " << gai_strerror(error)
            << std::endl;
#endif
    }
    else
#endif
    {
#if defined(_WIN32) || defined(__MINGW32__) || defined(__MINGW64__) || \
    defined(__CYGWIN__)
        if (prompt != nullptr)
            oss << "    > ";

        int lastError = WSAGetLastError();
        oss << "socket error: " << lastError
            << ", message: " << WinErrorToString(lastError);
#endif
    }

    return oss.str();
}


// References:
// https://en.cppreference.com/w/cpp/string/byte/strerror
// https://en.cppreference.com/w/c/string/byte/strerror
// https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strerror-s-strerror-s-wcserror-s-wcserror-s?view=msvc-170
// [Missing C11 strerrorlen_s function under MSVC 2017](https://stackoverflow.com/questions/44430141/missing-c11-strerrorlen-s-function-under-msvc-2017)
// https://docs.microsoft.com/en-us/windows/win32/winsock/error-codes-errno-h-errno-and-wsagetlasterror-2
// [How do I retrieve an error string from WSAGetLastError()?](https://stackoverflow.com/questions/3400922/how-do-i-retrieve-an-error-string-from-wsagetlasterror)
// https://linux.die.net/man/3/gai_strerror
