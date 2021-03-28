#pragma once

#include <cassert>

#if defined(_WIN32)
# define WIN32_LEAN_AND_MEAN
# include <Windows.h>
# include <shlwapi.h>
#elif defined(__linux__)
# include <unistd.h>
#else
# error Not tested yet!
#endif


inline bool is_path_exists(const char *path)
{
    assert(path != nullptr);

#if defined(_WIN32)
    return !!PathFileExistsA(path); // shlwapi.lib
#elif defined(__linux__)
    return access(path, F_OK) == 0;
#else
# error Not tested yet!
#endif
}


// References:
// https://github.com/lichuang/libraft/blob/11cb7dfb69c83ad0000671ad481e6bb63f4d3cbe/src/base/file_system_adaptor.cc#L10-L13
