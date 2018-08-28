#pragma once

#include "ConfigItem.hpp"
#include "IniConfigItemProvider.h"


template <typename T>
inline T LoadIniItem(const wchar_t *iniFile, const wchar_t *section, const wchar_t *name, T defaultValue)
{
    IniConfigItemProvider ini(iniFile);
    ConfigItem<T, wchar_t, ConfigItemConverter<T, wchar_t>> configItem(ini, section, name, defaultValue);
    configItem.Load();
    return configItem.GetValue();
}


template <typename T>
inline void StoreIniItem(const wchar_t *iniFile, const wchar_t *section, const wchar_t *name, T value)
{
    IniConfigItemProvider ini(iniFile);
    ConfigItem<T, wchar_t, ConfigItemConverter<T, wchar_t>> configItem(ini, section, name, value);
    configItem.Store();
}
