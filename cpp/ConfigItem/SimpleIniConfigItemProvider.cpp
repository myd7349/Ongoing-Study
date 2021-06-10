// Note:
// By default, SimpleIni will add space characters around equal sign when
// reading/writing key-value pairs:
// key = value

// Question: If we write an empty value with SimpleIni:
// key = 
// and read it via GetPrivateProfileString, what will we get? " " or ""?
#include "SimpleIniConfigItemProvider.h"

#include <cassert>


// TODO:
// Add Flush method for SimpleIniConfigItemProvider:
// void Flush() { simpleIni_.SaveFile(ini_.c_str()); }

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
