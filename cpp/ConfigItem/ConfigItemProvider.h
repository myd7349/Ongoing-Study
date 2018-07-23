#pragma once

#include <string>


template <typename CharT>
struct IConfigItemProvider
{
    typedef const CharT *StringT;

    virtual std::basic_string<CharT> Load(StringT section, StringT name, bool &ok) const = 0;
    virtual void Store(StringT section, StringT name, StringT value) = 0;
};
