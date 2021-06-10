#pragma once

#include <string>


template <typename CharT>
struct IConfigItemProvider
{
    IConfigItemProvider() {}

    typedef const CharT *StringT;

    virtual std::basic_string<CharT> GetConfigFilePath() = 0;

    virtual std::basic_string<CharT> Load(StringT section, StringT name, bool &ok) const = 0;
    virtual void Store(StringT section, StringT name, StringT value) = 0;

private:
    IConfigItemProvider(const IConfigItemProvider &);
    IConfigItemProvider &operator=(const IConfigItemProvider &);
};
