// 2015-01-28T16:21+08:00

#include <cassert>
#include <codecvt>
#include <exception>
#include <fstream>
#include <iostream>
#include <locale>
#include <vector>

#include <boost/program_options.hpp>

#include "azure_cloud_storage_service.h"
#include "../../common.h"

namespace po = boost::program_options;

// On MS Windows, Azure use wide strings.
#ifdef _WIN32
# include <tchar.h>
#else
# ifndef _tmain
#  define _tmain main
# endif

# ifndef _TCHAR
#  define _TCHAR char
# endif
#endif

template <typename CharT>
int ParseCmdlineArgs(const std::vector<std::basic_string<CharT>> &vargs, 
    AzureStorageAccountOptions &options)
{
    if (vargs.empty()) {
        ucerr << U("At least one command line argument is expected.\n");
        return EXIT_FAILURE;
    }

    try {
        // Declare a group of options that will be allowed only on command line.
        po::options_description generic_options("Generic options");
        std::string config_file_name;
        generic_options.add_options()
            ("config-file,c", po::value<std::string>(&config_file_name), "Configuration file path")
            ("help,h", "Display this information")
            ;

        // Declare a group of options that will be allowed both on command line and
        // in configuration file.
        po::options_description config_options("Configuration options");
        config_options.add_options()
            ("account-name,a", po::wvalue<utility::string_t>(&options.account_name)->required(), "Azure storage account name")
            ("primary-key,p", po::wvalue<utility::string_t>(&options.primary_access_key)->required(), "The primary access key")
            ("secondary-key,s", po::wvalue<utility::string_t>(&options.secondary_access_key), "The secondary access key")
#if 0
            ("end-point,e", po::wvalue<utility::string_t>(&options.endpoint_suffix)->default_value(U("core.windows.net")), "Endpoint suffix")
#else
            ("end-point,e", po::wvalue<utility::string_t>(&options.endpoint_suffix)->default_value(U("core.windows.net"), "core.windows.net"), "Endpoint suffix")
#endif
            ("use-https", po::value<bool>(&options.use_https)->implicit_value(true)->default_value(false), "Use \"HTTPS\" rather than \"HTTP\"")
            ("use-dev-storage", po::value<bool>(&options.use_dev_storage)->implicit_value(true)->default_value(false), "Use development storage account")
            ;

        po::variables_map args_map;
        po::store(po::basic_command_line_parser<CharT>(vargs).options(generic_options).allow_unregistered().run(), args_map);
        po::notify(args_map);

        if (vargs.size() < 2 || args_map.count("help")) {
            ucout << U("Usage: ") << GetProgName(vargs[0]) << U(" [options]\n");
            std::cout << po::options_description().add(generic_options).add(config_options) << std::endl;
            ucout << U("If \"--help\" is provided, then all other options will be ignored.\n")
                U("If \"--config-file\" is provided, then all \"Configuration options\"")
                U(" will be read from the specified configuration file.\n") << std::endl;
            return EXIT_FAILURE;
        }

        if (args_map.count("config-file")) {
            std::ifstream config_file_stream(config_file_name);
            if (config_file_stream) {
                po::store(po::parse_config_file(config_file_stream, config_options, true), args_map);
                po::notify(args_map);
            } else {
                std::cerr << "Open configuration file \"" << config_file_name << "\" failed.\n";
                return EXIT_FAILURE;
            }
        } else {
            //vargs.erase(vargs.begin()); // ???
            //po::store(po::parse_command_line<CharT>(argc, argv, config_options), args_map);
            po::store(po::basic_command_line_parser<CharT>(vargs).options(config_options).run(), args_map);
            po::notify(args_map);
        }
    } catch (const po::required_option &e) {
        RETURN_ON_FAILURE_MSG("required_option");
    } catch (const std::exception &e) {
        RETURN_ON_FAILURE_MSG("exception");
    }

    return EXIT_SUCCESS;
}

template <typename CharT>
int ParseCmdlineArgs(int argc, CharT *argv[], AzureStorageAccountOptions &options)
{
    assert(argc >= 1 && argv != nullptr);
    return ParseCmdlineArgs(po::detail::make_vector<CharT>(argv, argv + argc), options);
}

int _tmain(int argc, _TCHAR *argv[])
{
    ucin.imbue(std::locale(""));
    ucout.imbue(std::locale(""));
    //ucerr.imbue(std::locale(std::locale(""), 
    //    new std::codecvt_utf8<wchar_t>));

    AzureStorageAccountOptions storage_account_options;
#ifdef NDEBUG
    if (int rc = ParseCmdlineArgs(argc, argv, storage_account_options)) {
        PAUSE();
        return rc;
    }
#else
    // _DEBUG
    std::vector<utility::string_t> args;
    args.push_back(argv[0]);
    args.push_back(utility::string_t(U("--config-file=")) + GetProgName(argv[0]) + U(".cfg"));

    if (int rc = ParseCmdlineArgs(args, storage_account_options)) {
        PAUSE();
        return rc;
    }
#endif

    try {
        AzureCloudStorageService storage_service;
        return storage_service.run(storage_account_options);
    } catch (const azure::storage::storage_exception &e) {
        DumpAzureStorageError(e);
        return EXIT_FAILURE;
    } catch (const std::exception &e) {
        RETURN_ON_FAILURE_MSG("exception");
    } catch (...) {
        ucerr << U("Unknown exception!\n");
        return EXIT_FAILURE;
    }
}

// References:
// [24.3 Differences between the C Locale and the C++ Locales](http://stdcxx.apache.org/doc/stdlibug/24-3.html)
