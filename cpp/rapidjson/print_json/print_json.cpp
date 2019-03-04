#include <iostream>

#include "RapidJsonHelper.hpp"


int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        std::cout << "Usage: print_json [json-file] ...\n";
        return 0;
    }

    for (int i = 1; i < argc; ++i)
    {
        std::cout << ">> " << argv[i] << ":\n";

        rapidjson::Document document;
        if (LoadJsonDocument(document, argv[i]))
        {
            rapidjson::StringBuffer buffer;
            if (JsonDocumentToString(document, buffer))
                std::cout << buffer.GetString() << std::endl;
            else
                std::cerr << "JsonDocumentToString failed.\n";
        }
        else
        {
            std::cerr << "LoadJsonDocument failed.\n";
        }
    }
    
    return 0;
}
