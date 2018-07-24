#include "IniConfigItemProvider.h"

#include <cassert>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


std::wstring IniConfigItemProvider::Load(StringT section, StringT name, bool &ok) const
{
    assert(section != nullptr);
    assert(name != nullptr);

    if (GetPrivateProfileStringW(section, name, L"", buffer_, ARRAYSIZE(buffer_), ini_.c_str())
        < ARRAYSIZE(buffer_) - 1)
    {
        ok = true;
        return buffer_;
    }
    else
    {
        ok = false;
        return L"";
    }
}


void IniConfigItemProvider::Store(StringT section, StringT name, StringT value)
{
    assert(section != nullptr);
    assert(name != nullptr);
    assert(value != nullptr);

    WritePrivateProfileStringW(section, name, value, ini_.c_str());
}
