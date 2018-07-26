#include <iostream>
#include <locale>
#include <string>

#include "rapidjson_helper.h"


int main()
{
    using namespace rapidjson;

    std::wcout.imbue(std::locale(""));

    const wchar_t *json = L"{\"project\": \"rapidjson\", \"stars\": 10}";
    
    WDocument d;
    d.Parse(json);

    WValue &s = d[L"stars"];
    std::cout << s.GetInt() << std::endl;

    WValue &name = d[L"project"];
    std::wstring newName = L"ÌÚÑ¶ rapidjson";
    name.SetString(newName.c_str(), newName.length());
    std::wcout << name.GetString() << std::endl;

    WStringBuffer buffer;
    WWriter writer(buffer);
    d.Accept(writer);
    std::wcout << buffer.GetString() << std::endl;

    return 0;
}
