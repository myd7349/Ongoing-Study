#include "SimpleIniConfigItemProvider.h"

#include <cassert>


SimpleIniConfigItemProvider::SimpleIniConfigItemProvider(StringT ini)
    : ini_(ini), store_(false)
{
    simpleIni_.LoadFile(ini_.c_str());
}


SimpleIniConfigItemProvider::~SimpleIniConfigItemProvider()
{
    if (store_)
        simpleIni_.SaveFile(ini_.c_str());
}


// Difference between SimpleIniConfigItemProvider::Load and IniConfigItemProvider::Load:
// If `name` is not exist under `section`, then both of them returns false.
// If 'name' is exist, but its value is empty, then:
//     SimpleIniConfigItemProvider::Load returns true;
//     IniConfigItemProvider::Load returns false;
//
// Suppose you have an INI file `Config.ini`:
//     IniConfigItemProvider ini(_T("Config.ini"));
//     StringItem item(ini, _T("Default"), _T("Name"), _T("Non-empty default value"));
//     SimpleIniConfigItemProvider ini2(_T("Config.ini"));
//     StringItem item2(ini2, _T("Default"), _T("Name"), _T("Non-empty default value"));
//
// If `Name` is not exist under `Default`, then:
//     item.GetValue() == _T("Non-empty default value");
//     item2.GetValue() == _T("Non-empty default value");
//
// If `Name` is exist under `Default`, but with an empty value, then:
//     item.GetValue() == _T("Non-empty default value");
//     item2.GetValue() == _T("");

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
    
    if (!store_)
        store_ = true;
}
