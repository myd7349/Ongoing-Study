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
        bool autoStore = true, ConverterT converter = ConverterT())
        : provider_(provider)
        , section_(section)
        , name_(name)
        , value_(defaultValue)
        , default_(defaultValue)
        , autoStore_(autoStore)
        , dirty_(false)
        , converter_(converter)
    {
        assert(section != nullptr);
        assert(name != nullptr);
    }

    ~ConfigItem()
    {
        if (autoStore_)
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

            if (!dirty_)
                dirty_ = true;
        }

        return value_;
    }

    bool IsEmpty() const
    {
        return value_ == default_;
    }

    bool IsDirty() const
    {
        return dirty_;
    }

    bool IsAutoStore() const
    {
        return autoStore_;
    }

    bool SetAutoStore(bool autoStore)
    {
        autoStore_ = autoStore;
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
            return ok;
        }
        else
        {
            return false;
        }
    }

    void Store()
    {
        if (dirty_)
        {
            std::basic_string<CharT> value = ToString();
            provider_.Store(section_.c_str(), name_.c_str(), value.c_str());

            dirty_ = false;
        }
    }

private:
    IConfigItemProvider<CharT> &provider_;
    std::basic_string<CharT> section_;
    std::basic_string<CharT> name_;
    T default_;
    T value_;
    bool autoStore_;
    bool dirty_;
    ConverterT converter_;
};


template <typename T, typename CharT>
inline T LoadItem(IConfigItemProvider<CharT> &provider, const CharT *section, const CharT *name, T defaultValue)
{
    ConfigItem<T, CharT, ConfigItemConverter<T, CharT>> configItem(provider, section, name, defaultValue);
    configItem.Load();
    return configItem.GetValue();
}


template <typename T, typename CharT>
inline void StoreItem(IConfigItemProvider<CharT> &provider, const CharT *section, const CharT *name, T value)
{
    ConfigItem<T, CharT, ConfigItemConverter<T, CharT>> configItem(provider, section, name, value);
    configItem.Store();
}


typedef ConfigItem<int> IntItem;
typedef ConfigItem<std::wstring> StringItem;
