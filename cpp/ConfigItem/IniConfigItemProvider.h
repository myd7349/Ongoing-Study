#pragma once

#include <vector>

#include "ConfigItemProvider.h"


class IniConfigItemProvider : public IConfigItemProvider<wchar_t>
{
public:
    IniConfigItemProvider(StringT ini)
        : ini_(ini), buffer_(1024)
    {
    }

    virtual std::wstring Load(StringT section, StringT name, bool &ok) const;
    virtual void Store(StringT section, StringT name, StringT value);

private:
    std::wstring ini_;
    mutable std::vector<wchar_t> buffer_;
};
