#pragma once

#include <algorithm>

#pragma warning(disable: 4005)
#include <rapidjson/document.h>
#pragma warning(default: 4005)


template <typename ContainerT>
bool ArrayFromJsonValue(ContainerT &container, const rapidjson::Value &value, bool strictMode)
{
    ContainerT c;

    if (!value.IsArray())
        return false;

    for (rapidjson::SizeType i = 0; i < value.Size(); ++i)
    {
        if (value[i].Is<typename ContainerT::value_type>())
        {
            c.push_back(value[i].Get<typename ContainerT::value_type>());
        }
        else
        {
            if (strictMode)
                return false;
        }
    }

    std::swap(container, c);
    return true;
}


template <typename ContainerT>
void ArrayToJsonValue(const ContainerT &container, rapidjson::Value &value, rapidjson::Value::AllocatorType &allocator)
{
    if (!value.IsArray())
        value.SetArray();

    for (typename ContainerT::const_iterator it = container.cbegin(); it != container.cend(); ++it)
        value.PushBack(*it, allocator);
}


