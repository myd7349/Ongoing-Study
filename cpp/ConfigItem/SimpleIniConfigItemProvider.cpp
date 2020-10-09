#include "SimpleIniConfigItemProvider.h"

#include <cassert>


SimpleIniConfigItemProvider::SimpleIniConfigItemProvider(StringT ini)
    : ini_(ini)
{
	simpleIni_.LoadFile(ini_.c_str());
}


SimpleIniConfigItemProvider::~SimpleIniConfigItemProvider()
{
    simpleIni_.SaveFile(ini_.c_str());
}


std::wstring SimpleIniConfigItemProvider::Load(StringT section, StringT name, bool &ok) const
{
    assert(section != nullptr);
    assert(name != nullptr);
    
    bool multiple;
    const wchar_t *pszValue = simpleIni_.GetValue(section, name, nullptr, &multiple);
    if (pszValue != nullptr)
    {
        ok = true;
        return pszValue;
    }
    else
    {
        ok = false;
        return L"";
    }
}


void SimpleIniConfigItemProvider::Store(StringT section, StringT name, StringT value)
{
    assert(section != nullptr);
    assert(name != nullptr);
    assert(value != nullptr);
    
    simpleIni_.SetValue(section, name, value);
}
