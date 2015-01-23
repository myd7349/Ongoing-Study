// 2015-01-13T15:29+08:00
// Yet another INI file parsing example with Boost.Program_options.
// The previous INI parsing example I wrote can be found here:
// https://github.com/myd7349/Ongoing-Study/tree/master/cpp/Boost/property_tree/ini_parser/ini_parser_test

#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>

#include "../../../common.h"

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
            // Boost.Property_tree.ini_parser will treat "true", "1" as true, and "false", "0" as false.
            // So what about Boost.Program_options?
            ("use-https", Opt::value<bool>(&options.useHttps), "Use \"HTTPS\" rather than \"HTTP\"")
            ("use-dev-storage", Opt::value<bool>(&options.useDevStorage), "Use development storage account")
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
            // will always be wrongly parsed.

            std::wcout << options;
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
