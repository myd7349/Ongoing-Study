#pragma once

#include <cassert>

#include "ConfigItemProvider.h"


class IniConfigItemProvider : public IConfigItemProvider<wchar_t>
{
public:
    IniConfigItemProvider(StringT ini) : ini_(ini)
    {
        assert(ini_ != nullptr);
    }

    virtual std::wstring Load(StringT section, StringT name, bool &ok) const;
    virtual void Store(StringT section, StringT name, StringT value);

private:
    StringT ini_;
    mutable wchar_t buffer_[1024];
};
