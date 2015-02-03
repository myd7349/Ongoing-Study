// 2015-01-28T16:21+08:00

#include <cassert>
#include <exception>
#include <fstream>
#include <iostream>
#include <vector>

#include <boost/program_options.hpp>

#include "azure_cloud_storage_service.h"
#include "../../common.h"

namespace Opt = boost::program_options;

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
        Opt::options_description generic_options("Generic options");
        std::string config_file_name;
        generic_options.add_options()
            ("config-file,c", Opt::value<std::string>(&config_file_name), "Configuration file path")
            ("help,h", "Display this information")
            ;

        // Declare a group of options that will be allowed both on command line and
        // in configuration file.
        Opt::options_description config_options("Configuration options");
        config_options.add_options()
            ("account-name,a", Opt::wvalue<utility::string_t>(&options.account_name), "Azure storage account name")
            ("primary-key,p", Opt::wvalue<utility::string_t>(&options.primary_access_key), "The primary access key")
            ("secondary-key,s", Opt::wvalue<utility::string_t>(&options.secondary_access_key), "The secondary access key")
#if 0
            ("end-point,e", Opt::wvalue<utility::string_t>(&options.end_point_suffix)->default_value(U("core.windows.net")), "Endpoint suffix")
#else
            ("end-point,e", Opt::wvalue<utility::string_t>(&options.end_point_suffix)->default_value(U("core.windows.net"), "core.windows.net"), "Endpoint suffix")
#endif
            ("use-https", Opt::value<bool>(&options.use_https)->implicit_value(true), "Use \"HTTPS\" rather than \"HTTP\"")
            ("use-dev-storage", Opt::value<bool>(&options.use_dev_storage)->implicit_value(true), "Use development storage account")
            ;

        Opt::variables_map args_map;
        Opt::store(Opt::basic_command_line_parser<CharT>(vargs).options(generic_options).allow_unregistered().run(), args_map);
        Opt::notify(args_map);

        if (vargs.size() < 2 || args_map.count("help")) {
            ucout << U("Usage: ") << GetProgName(vargs[0]) << U(" [options]\n");
            std::cout << Opt::options_description().add(generic_options).add(config_options) << std::endl;
            ucout << U("If \"--help\" is provided, then all other options will be ignored.\n")
                U("If \"--config-file\" is provided, then all \"Configuration options\"")
                U(" will be read from the specified configuration file.\n") << std::endl;
            return EXIT_FAILURE;
        }

        if (args_map.count("config-file")) {
            std::ifstream config_file_stream(config_file_name);
            if (config_file_stream) {
                Opt::store(Opt::parse_config_file(config_file_stream, config_options, true), args_map);
                Opt::notify(args_map);
            } else {
                std::cerr << "Open configuration file \"" << config_file_name << "\" failed.\n";
            }
        } else {
            //vargs.erase(vargs.begin()); // ???
            //Opt::store(Opt::parse_command_line<CharT>(argc, argv, config_options), args_map);
            Opt::store(Opt::basic_command_line_parser<CharT>(vargs).options(config_options).run(), args_map);
            Opt::notify(args_map);
        }
    } catch (const std::exception &e) {
        RETURN_ON_FAILURE_MSG("exception");
    }

    return EXIT_SUCCESS;
}

template <typename CharT>
int ParseCmdlineArgs(int argc, CharT *argv[], AzureStorageAccountOptions &options)
{
    assert(argc >= 1 && argv != nullptr);
    return ParseCmdlineArgs(Opt::detail::make_vector<CharT>(argv, argv + argc), options);
}

int _tmain(int argc, _TCHAR *argv[])
{
    AzureStorageAccountOptions storage_account_options;
#ifdef NDEBUG
    if (int rc = ParseCmdlineArgs(argc, argv, storage_account_options)) {
        return rc;
    }
#else
    // _DEBUG
    std::vector<utility::string_t> args;
    args.push_back(argv[0]);
    args.push_back(utility::string_t(U("--config-file=")) + GetProgName(argv[0]) + U(".cfg"));

    if (int rc = ParseCmdlineArgs(args, storage_account_options)) {
        return rc;
    }
#endif

    try {
        AzureCloudStorageService storage_service;
        return storage_service.run(storage_account_options);
    } catch (const azure::storage::storage_exception &e) {
        RETURN_ON_FAILURE_MSG("storage_exception");
    } catch (const std::exception &e) {
        RETURN_ON_FAILURE_MSG("exception");
    } catch (...) {
        ucerr << U("Unknown exception!\n");
        return EXIT_FAILURE;
    }
}
