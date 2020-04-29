#include <cstdlib>
#include <exception>
#include <iostream>
#include <string_view>

#include <simdjson.h>
//#include <simdjson/document.h>

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

            auto json_result = simdjson::padded_string::load(argv[i]);
            if (json_result.error() != simdjson::SUCCESS) {
              std::cerr << "Failed to load JSON file: " << json_result.error() << '\n';
              return EXIT_FAILURE;
            }

            auto &json = json_result.value();

            simdjson::dom::parser parser;
            auto parse_result = parser.parse(json.data(), json.length());

            std::cout << parse_result << '\n';
        }
        catch (const std::exception &exc)
        {
            std::cerr << "Failed to load \"" << argv[i] << "\": " << exc.what() << '\n';
        }
    }
    
    return 0;
}
