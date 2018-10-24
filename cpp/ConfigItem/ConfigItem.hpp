#pragma once

#include "ConfigItemConverter.hpp"
#include "ConfigItemProvider.h"


template <typename T, typename CharT = wchar_t,
    typename ConverterT = ConfigItemConverter<T, CharT>>
struct ConfigItem
{
    typedef const CharT *StringT;

    ConfigItem(IConfigItemProvider<CharT> &provider,
        StringT section, StringT name, T defaultValue,
        bool autoSync = true, ConverterT converter = ConverterT())
        : provider_(provider)
        , section_(section)
        , name_(name)
        , value_(defaultValue)
        , default_(defaultValue)
        , autoSync_(autoSync)
        , dirty_(false)
        , converter_(converter)
    {
        assert(section != nullptr);
        assert(name != nullptr);

        if (autoSync_)
            Load();
    }

    // When T = StringT, this form will be identical to the one above.
    // So you are not allowed to use ConfigItem<const char *, char> or
    // ConfigItem<const wchar_t *, wchar_t>.
    // Given that these two kind of usages are also unsafe, I think the
    // potential ambiguity is not a big deal. 
    // If you really want to define a string-likely ConfigItem, use
    // ConfigItem<std::string, char>/ConfigItem<std::wstring, wchar_t> instead.
    ConfigItem(IConfigItemProvider<CharT> &provider,
        StringT section, StringT name, StringT defaultValue,
        bool autoSync = true, ConverterT converter = ConverterT())
        : provider_(provider)
        , section_(section)
        , name_(name)
        , autoSync_(autoSync)
        , dirty_(false)
        , converter_(converter)
    {
        assert(section != nullptr);
        assert(name != nullptr);

        bool ok;
        value_ = default_ = converter_.FromString(defaultValue, ok, T());

        if (autoSync_)
            Load();
    }

    ~ConfigItem()
    {
        if (autoSync_ && dirty_)
            Store();
    }

    const std::basic_string<CharT> &GetSection() const
    {
        return section_;
    }

    const std::basic_string<CharT> &GetName() const
    {
        return name_;
    }

    T GetDefaultValue() const
    {
        return default_;
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
            dirty_ = true;
        }

        return value_;
    }

    T Reset()
    {
        return SetValue(default_);
    }

    bool IsEmpty() const
    {
        return value_ == default_;
    }

    bool IsDirty() const
    {
        return dirty_;
    }

    bool IsAutoSync() const
    {
        return autoSync_;
    }

    bool SetAutoSync(bool autoSync)
    {
        autoSync_ = autoSync;
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

    bool Load()
    {
        bool ok;
        std::basic_string<CharT> value = provider_.Load(section_.c_str(), name_.c_str(), ok);
        if (ok)
        {
            FromString(value.c_str(), ok);
            if (ok)
                dirty_ = false;

            return ok;
        }
        else
        {
            return false;
        }
    }

    void Store()
    {
        std::basic_string<CharT> value = ToString();
        provider_.Store(section_.c_str(), name_.c_str(), value.c_str());

        dirty_ = false;
    }

private:
    IConfigItemProvider<CharT> &provider_;
    std::basic_string<CharT> section_;
    std::basic_string<CharT> name_;
    T default_;
    T value_;
    bool autoSync_;
    bool dirty_;
    ConverterT converter_;
};


template <typename T, typename CharT>
inline T LoadItem(IConfigItemProvider<CharT> &provider, const CharT *section, const CharT *name, T defaultValue)
{
    ConfigItem<T, CharT, ConfigItemConverter<T, CharT>> configItem(provider, section, name, defaultValue, true);
    return configItem.GetValue();
}


template <typename T, typename CharT>
inline T LoadItem(IConfigItemProvider<CharT> &provider, const CharT *section, const CharT *name, const CharT *defaultValue)
{
    ConfigItem<T, CharT, ConfigItemConverter<T, CharT>> configItem(provider, section, name, defaultValue, true);
    return configItem.GetValue();
}


template <typename T, typename CharT>
inline void StoreItem(IConfigItemProvider<CharT> &provider, const CharT *section, const CharT *name, T value)
{
    ConfigItem<T, CharT, ConfigItemConverter<T, CharT>> configItem(provider, section, name, value, false);
    configItem.Store();
}


typedef ConfigItem<int>          IntItem;
typedef ConfigItem<bool>         BoolItem;
typedef ConfigItem<double>       DoubleItem;
typedef ConfigItem<std::wstring> StringItem;
