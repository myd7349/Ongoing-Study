#pragma once

#include <vector>

#include "SimpleIni.h"

#include "ConfigItemProvider.h"


class SimpleIniConfigItemProvider : public IConfigItemProvider<wchar_t>
{
public:
    SimpleIniConfigItemProvider(StringT ini);
    ~SimpleIniConfigItemProvider();

    virtual std::basic_string<CharT> GetConfigFilePath()
    {
        return ini_;
    }

    virtual std::wstring Load(StringT section, StringT name, bool &ok) const;
    virtual void Store(StringT section, StringT name, StringT value);

private:
    std::wstring ini_;
    CSimpleIniW simpleIni_;
    bool store_;
};
