#include <cstdio>
#include <iostream>
#include <locale>
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"


int main()
{
    using namespace rapidjson;

    Document document(kObjectType);
    Document::AllocatorType &allocator = document.GetAllocator();

    Value copyEvent(kObjectType);
    copyEvent.AddMember("ID", 0, allocator);
    copyEvent.AddMember("Name", "Copy", allocator);
    copyEvent.AddMember("DateTime", "2018-07-28T11:37+08:00", allocator);

    Value pasteEvent(kObjectType);
    pasteEvent.AddMember("ID", 1, allocator);
    pasteEvent.AddMember("Name", "Paste", allocator);
    pasteEvent.AddMember("DateTime", "2018-07-28T11:38+08:00", allocator);

    Value eventsArray(kArrayType);
    eventsArray.PushBack(copyEvent, allocator);
    eventsArray.PushBack(pasteEvent, allocator);

    document.AddMember("Events", eventsArray, allocator);

    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer);
    document.Accept(writer);
    std::cout << buffer.GetString() << std::endl;

    return 0;
}
