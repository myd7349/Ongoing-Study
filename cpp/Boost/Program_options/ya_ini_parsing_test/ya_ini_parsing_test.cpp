// 2015-01-13T15:29+08:00
// Yet another INI file parsing example with Boost.Program_options.
// The previous INI parsing example I wrote can be found here:
// https://github.com/myd7349/Ongoing-Study/tree/master/cpp/Boost/property_tree/ini_parser/ini_parser_test 
// 2015-01-16T15:12+08:00
// This example also demonstrates two elegant ways to parse boolean options.

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <boost/any.hpp>
#include <boost/program_options.hpp>

#include "../../../common.h"

// Change between 0 and 1, and see the help information for "--use-https"
// and "--use-dev-storage".
#define PARSE_USE_HTTPS_OPTION_MYSELF (1)

struct Options {
    std::wstring accountName;
    std::wstring primaryAccessKey;
    std::wstring secondaryAccessKey;
    std::wstring endPoint;
    bool useHttps;
    bool useDevStorage;
};

namespace Opt = boost::program_options;

std::wostream &operator<<(std::wostream &os, const Options &options)
{
    os << L"Account name: " << options.accountName << std::endl;
    os << L"Primary access key: " << options.primaryAccessKey << std::endl;
    os << L"Secondary access key: " << options.secondaryAccessKey << std::endl;
    os << L"Endpoint suffix: " << options.endPoint << std::endl;
    os << std::boolalpha;
    os << L"Use HTTPS: " << options.useHttps << std::endl;
    os << L"Use development storage account: " << options.useDevStorage << std::endl;
    return os;
}

int main()
{
    try {
        Options options;

        Opt::options_description configOptions("Options");
        configOptions.add_options()
            ("account-name,a", Opt::wvalue<std::wstring>(&options.accountName), "Azure storage account name")
            ("primary-key,p", Opt::wvalue<std::wstring>(&options.primaryAccessKey), "The primary access key")
            ("secondary-key,s", Opt::wvalue<std::wstring>(&options.secondaryAccessKey), "The secondary access key")
#if 0
            ("end-point,e", Opt::wvalue<std::wstring>(&options.endPoint)->default_value(L"core.windows.net"), "Endpoint suffix")
#else
            ("end-point,e", Opt::wvalue<std::wstring>(&options.endPoint)->default_value(L"core.windows.net", "core.windows.net"), "Endpoint suffix")
#endif

#if defined(PARSE_USE_HTTPS_OPTION_MYSELF) && PARSE_USE_HTTPS_OPTION_MYSELF
            ("use-https", "Use \"HTTPS\" rather than \"HTTP\"")
            ("use-dev-storage", "Use development storage account")
#else
            ("use-https", Opt::value<bool>(&options.useHttps)->implicit_value(true), "Use \"HTTPS\" rather than \"HTTP\"")
            ("use-dev-storage", Opt::value<bool>(&options.useDevStorage)->implicit_value(true), "Use development storage account")
#endif
            ;

        Opt::variables_map optionsMap;
        std::ifstream configFileStream("example.configuration");
        if (configFileStream) {
            Opt::store(Opt::parse_config_file(configFileStream, configOptions, true), optionsMap);
            Opt::notify(optionsMap);

            // For boolean value, we had better not parse them like this:
            //
            //options.useHttps = optionsMap.count("use-https") > 0;
            //options.useDevStorage = optionsMap.count("use-dev-storage") > 0;
            //
            // since those lines in configuration file:
            //   use-https = false
            //   use-dev-storage = 0
            // will always be wrongly parsed in this way.
            //
            // If you really want to parse them yourself, then do it like this:
#if defined(PARSE_USE_HTTPS_OPTION_MYSELF) && PARSE_USE_HTTPS_OPTION_MYSELF
# if 0
            // Oops! boost::bad_any_cast.
            // We CANNOT cast a string "false" to a boolean false directly.
            // We should convert "false" to "0", and then call boost::any_cast/boost::lexical_cast.
            options.useHttps = optionsMap.count("use-https") > 0 ?
                optionsMap["use-https"].as<bool>() : false;
            options.useDevStorage = optionsMap.count("use-dev-storage") > 0 ?
                optionsMap["use-dev-storage"].as<bool>() : false;
# else
            // Boost.Property_tree.ini_parser will treat "true", "1", "yes" as true, and "false", "0", "no" as false.
            // 
            // Internally, Boost.program_options calls boost::program_options::validate to
            // validate boolean values. That is:
            //   1. Any of "1", "true", "yes", "on" will be converted to "1".
            //   2. Any of "0", "false", "no", "off" will be converted to "0".
            // Please read libs/program_options/src/value_semantic.cpp for more details.
            if (optionsMap.count("use-https") > 0) {
                boost::any v;
                std::vector<std::string> xs {optionsMap["use-https"].as<std::string>()};
                Opt::validate(v, xs, reinterpret_cast<bool *>(NULL), 0);
                options.useHttps = boost::any_cast<bool>(v);
            } else {
                options.useHttps = false;
            }

            if (optionsMap.count("use-dev-storage") > 0) {
                boost::any v;
                std::vector<std::string> xs {optionsMap["use-dev-storage"].as<std::string>()};
                Opt::validate(v, xs, reinterpret_cast<bool *>(NULL), 0);
                options.useDevStorage = boost::any_cast<bool>(v);
            } else {
                options.useDevStorage = false;
            }
# endif
#endif

            std::cout << configOptions;

            std::wcout << L"\n\n" << options;
        } else {
            std::cerr << "Open configuration file failed.\n";
            return EXIT_FAILURE;
        }
    } catch (const std::exception &e) {
        RETURN_ON_FAILURE_MSG("exception");
    }

    PAUSE();
    return 0;
}

// References:
// [In Boost::Program_Options, how to set default value for wstring?](http://stackoverflow.com/questions/6921196/in-boostprogram-options-how-to-set-default-value-for-wstring)
