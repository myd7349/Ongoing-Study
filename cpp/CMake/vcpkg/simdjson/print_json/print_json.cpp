#include <exception>
#include <iostream>
#include <string_view>

#include <simdjson/jsonioutil.h>
#include <simdjson/jsonparser.h>


int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        std::cout << "Usage: print_json [json-file] ...\n";
        return 0;
    }

    for (int i = 1; i < argc; ++i)
    {
        try
        {
            std::cout << ">> " << argv[i] << ":\n";

            std::string_view json = get_corpus(argv[i]);
            ParsedJson document = build_parsed_json(json);
            document.printjson(std::cout);

            std::cout << '\n';
        }
        catch (const std::exception &exc)
        {
            std::cerr << "Failed to load \"" << argv[i] << "\": " << exc.what() << '\n';
        }
    }
    
    return 0;
}
