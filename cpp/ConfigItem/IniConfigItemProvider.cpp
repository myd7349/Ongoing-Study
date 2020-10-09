#include "IniConfigItemProvider.h"

#include <cassert>
#include <sys/stat.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


std::wstring IniConfigItemProvider::Load(StringT section, StringT name, bool &ok) const
{
    assert(section != nullptr);
    assert(name != nullptr);

    DWORD dwRes = GetPrivateProfileStringW(section, name, L"",
        buffer_.data(), static_cast<DWORD>(buffer_.size()), ini_.c_str());
    if (dwRes > 0 && dwRes < buffer_.size() - 1)
    {
        ok = true;
        return buffer_.data();
    }
    else
    {
        struct _stat fileInfo;
        if (_wstat(ini_.c_str(), &fileInfo) != 0)
        {
            ok = false;
            return L"";
        }

        buffer_.resize(fileInfo.st_size + 1);
        if (buffer_.size() < 3)
            buffer_.resize(4);

        dwRes = GetPrivateProfileStringW(section, name, L"",
            buffer_.data(), static_cast<DWORD>(buffer_.size()), ini_.c_str());
        if (dwRes > 0 && dwRes < buffer_.size() - 1)
        {
            ok = true;
            return buffer_.data();
        }

        ok = false;
        return L"";
    }
}


void IniConfigItemProvider::Store(StringT section, StringT name, StringT value)
{
    assert(section != nullptr);
    assert(name != nullptr);
    assert(value != nullptr);
    
    // If the string is too long:
    // For example, I tried to save the base64 of a 8M .bmp file, it just failed.
    // ERROR_MORE_DATA: 0x000000ea
    BOOL bRes = WritePrivateProfileStringW(section, name, value, ini_.c_str());
    assert(bRes);
}

// References:
// [GetPrivateProfileString - Buffer length](https://stackoverflow.com/questions/10507927/getprivateprofilestring-buffer-length)
