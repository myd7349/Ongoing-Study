#include <cstdio>
#include <iostream>
#include <locale>
#include <string>

#include "rapidjson/filereadstream.h"

#include "rapidjson_helper.h"


int main()
{
    using namespace rapidjson;

    std::wcout.imbue(std::locale(""));

    std::FILE *file;
    fopen_s(&file, "example.json", "r");
    if (file == nullptr)
    {
        std::cerr << "Failed to open JSON file.\n";
        return 1;
    }

    const int ReadBufferSize = 65536;
    char readBuffer[ReadBufferSize];
    FileReadStream reader(file, readBuffer, ReadBufferSize);
    
#if 0
    WDocument d;
    d.ParseStream(reader);

    const WValue &dateTime = d[L"DateTime"];
    std::wcout << L"DateTime" << dateTime.GetString() << std::endl;
#else
    Document d;
    d.ParseStream(reader);

    const Value &dateTime = d["DateTime"];
    std::cout << "DateTime: " << dateTime.GetString() << std::endl;

    const Value &events = d["Events"];
    for (SizeType i = 0; i < events.Size(); ++i)
        std::cout << events[i]["ID"].GetInt() << ": " << events[i]["Name"].GetString() << std::endl;
#endif

    return 0;
}
