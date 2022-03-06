#pragma once

#include "ConfigItemConverter.hpp"
#include "ConfigItemProvider.h"


template <typename T, typename CharT = wchar_t,
    typename ConverterT = ConfigItemConverter<T, CharT>>
struct ConfigItem
{
    typedef const CharT *StringT;

    ConfigItem(IConfigItemProvider<CharT> &provider,
        StringT section, StringT name, T defaultValue = T(),
        bool autoSync = true, ConverterT converter = ConverterT())
        : provider_(provider)
        , section_(section)
        , name_(name)
        , value_(defaultValue)
        , default_(defaultValue)
        , autoSync_(autoSync)
        , dirty_(true)//, dirty_(!PathFileExists(provider.GetConfigFilePath().c_str()))
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
        StringT section, StringT name, StringT defaultValue = StringT(),
        bool autoSync = true, ConverterT converter = ConverterT())
        : provider_(provider)
        , section_(section)
        , name_(name)
        , autoSync_(autoSync)
        , dirty_(true)//, dirty_(!PathFileExists(provider.GetConfigFilePath().c_str()))
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

    // Not:
    // T operator()() const
    operator T() const
    {
        return GetValue();
    }

    T SetValue(T value/*, bool store = true*/)
    {
        if (value_ != value)
        {
            value_ = value;
            dirty_ = true;
        }

        //if (store)
        //    Store();

        return value_;
    }
    
    T operator=(T value)
    {
        return SetValue(value);
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
inline T LoadItem(IConfigItemProvider<CharT> &provider, const CharT *section, const CharT *name, T defaultValue = T())
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


// References:
// https://github.com/OzanCansel/fsconfig
// https://github.com/ABRG-Models/morphologica/blob/main/morph/Config.h
// https://github.com/slowburn-dev/DataConfig
// https://en.cppreference.com/w/cpp/language/implicit_conversion
// [Why override operator()?](https://stackoverflow.com/questions/317450/why-override-operator)
// [What is an "operator int" function?](https://stackoverflow.com/questions/3814865/what-is-an-operator-int-function)
/*
// http://www.cppblog.com/shaker/archive/2006/10/03/13281.html
 class  CSettingManager
 {
 private :
    std::map < std:: string ,std:: string >  m_Settings;
    std:: string  m_Filename;
 public :
     void  Load(std:: string  server, std:: string  character);
     void  Save(  void  );
     const  std:: string &  Get( std:: string  key,  const  std:: string &  default_value = std:: string () )
     {
        std::map < std:: string ,std:: string > ::iterator itor =  m_Settings.find(key);
         if  ( itor == m_Settings.end() )
         {
            Set(key,default_value);
             return  default_value;
        }
         return  itor -> second;
    }
     void  Set(std:: string  key,  const  std:: string &  value)
     {
        m_Settings[key] = value;
    }
    template < class  T >  T Get( std:: string  key, T default_value = T( 0 ))
     {
        std::map < std:: string ,std:: string > ::iterator itor =  m_Settings.find(key);
         if  ( itor == m_Settings.end() )
         {
            Set < T > (key,default_value);
             return  default_value;
        }
         return  boost::lexical_cast < T,std:: string > (itor -> second);
    }
    template < class  T >   void  Set(std:: string  key, T value)
     {
        m_Settings[key] = boost::lexical_cast < std:: string ,T > (value);
    }
} ;
*/
