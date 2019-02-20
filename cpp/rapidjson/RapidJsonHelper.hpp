#pragma once

#include <algorithm>
#include <cassert>
#include <fstream>

#pragma warning(disable: 4005)
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/pointer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#pragma warning(default: 4005)


inline bool LoadJsonDocument(rapidjson::Document &document, const wchar_t *jsonFilePath)
{
    assert(jsonFilePath != nullptr);

    std::ifstream stream;
    stream.open(jsonFilePath);

    if (!stream.is_open())
        return false;

    rapidjson::IStreamWrapper jsonStream(stream);

    return !document.ParseStream(jsonStream).IsNull();
}


inline bool JsonDocumentToString(const rapidjson::Document &document, rapidjson::StringBuffer &buffer)
{
    rapidjson::PrettyWriter<rapidjson::StringBuffer> prettyWriter(buffer);
    return document.Accept(prettyWriter);
}


inline bool StoreJsonDocument(const rapidjson::Document &document, const wchar_t *jsonFilePath)
{
    rapidjson::StringBuffer buffer;
    if (!JsonDocumentToString(document, buffer))
        return false;

    std::ofstream jsonStream(jsonFilePath);
    if (!jsonStream.is_open())
        return false;

    jsonStream.write(buffer.GetString(), static_cast<std::streamsize>(buffer.GetSize()));
    jsonStream.close();
    return true;
}


inline bool JsonValueFromPointer(rapidjson::Document &document, const char *pointer, rapidjson::Value &value)
{
    assert(pointer != nullptr);

    const rapidjson::Value *valuePtr = rapidjson::Pointer(pointer).Get(document);
    if (valuePtr == nullptr)
        return false;

    value.CopyFrom(*valuePtr, document.GetAllocator());
    return true;
}


template <typename ContainerT>
inline bool ArrayFromJsonValue(ContainerT &container, const rapidjson::Value &value, bool strictMode)
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
inline void ArrayToJsonValue(const ContainerT &container, rapidjson::Value &value, rapidjson::Value::AllocatorType &allocator)
{
    if (!value.IsArray())
        value.SetArray();

    for (typename ContainerT::const_iterator it = container.cbegin(); it != container.cend(); ++it)
        value.PushBack(*it, allocator);
}
