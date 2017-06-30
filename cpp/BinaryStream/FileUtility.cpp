#include "FileUtility.h"

#ifdef _WIN32
#define STRICT 1
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>
#endif


bool IsExists(const std::wstring &fileName)
{
#ifdef _WIN32
    return !!PathFileExists(fileName.c_str());
#else
#error Not tested yet!
#endif
}
