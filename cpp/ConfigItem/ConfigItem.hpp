#pragma once

#include "ConfigItemConverter.hpp"
#include "ConfigItemProvider.h"


template <typename T,
    typename CharT = wchar_t,
    typename ConverterT = ConfigItemConverter<T, CharT>>
struct ConfigItem
{
    typedef const CharT *StringT;

    ConfigItem(StringT section, StringT name, T value = T(), T defaultValue = T(),
        ConverterT converter = ConverterT())
        : section_(section)
        , name_(name)
        , value_(value)
        , default_(defaultValue)
        , dirty_(false)
        , converter_(converter)
    {
        assert(section != nullptr);
        assert(name != nullptr);
    }

    const std::basic_string<CharT> &GetSection() const
    {
        return section_;
    }

    const std::basic_string<CharT> &GetName() const
    {
        return name_;
    }

    T GetValue() const
    {
        if (IsEmpty())
            return GetDefaultValue();

        return value_;
    }

    T SetValue(T value)
    {
        if (value_ != value)
        {
            value_ = value;

            if (!dirty_)
                dirty_ = true;
        }

        return value_;
    }

    T GetDefaultValue() const
    {
        return default_;
    }

    bool IsEmpty() const
    {
        return value_ == default_;
    }

    bool IsDirty() const
    {
        return dirty_;
    }

    T FromString(StringT s, bool &ok)
    {
        T value = converter_.FromString(s, ok);
        if (ok)
            return SetValue(value);

        return GetValue();
    }

    std::basic_string<CharT> ToString() const
    {
        return converter_.ToString(GetValue());
    }

    bool Load(IConfigItemProvider<CharT> &provider)
    {
        bool ok;
        std::basic_string<CharT> value = provider.Load(section_.c_str(), name_.c_str(), ok);
        if (ok)
        {
            FromString(value.c_str(), ok);
            return ok;
        }
        else
        {
            return false;
        }
    }

    void Store(IConfigItemProvider<CharT> &provider, bool cleanDirtyFlag = true)
    {
        std::basic_string<CharT> value = ToString();
        provider.Store(section_.c_str(), name_.c_str(), value.c_str());

        if (cleanDirtyFlag)
            dirty_ = false;
    }

private:
    std::basic_string<CharT> section_;
    std::basic_string<CharT> name_;
    T default_;
    T value_;
    bool dirty_;
    ConverterT converter_;
};


typedef ConfigItem<int> IntItem;
typedef ConfigItem<std::wstring> StringItem;
