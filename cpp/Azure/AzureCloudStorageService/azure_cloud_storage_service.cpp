// 2015-01-28T08:56+08:00

#include "azure_cloud_storage_service.h"

#include <cstdlib>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <boost/progress.hpp>

#include "../../common.h"
#include "../../dividing_lines.h"
#include "../../split_args.h"

#include "Command/clear_command.h"
#include "Command/exit_command.h"
#include "Command/help_command.h"
#include "Command/Blob/cd_command.h"
#include "Command/Blob/get_command.h"
#include "Command/Blob/list_command.h"
#include "Command/Blob/put_command.h"
#include "Command/Blob/rm_command.h"

#ifdef _MSC_VER
# ifdef NDEBUG
#  pragma comment(lib, "cpprest120_2_3.lib")
# else
#  pragma comment(lib, "cpprest120d_2_3.lib")
# endif

# pragma comment(lib, "wastorage.lib")
#endif

AzureCloudStorageService::AzureCloudStorageService()
    : available_commands_ ({ 
          CD_COMMAND_STR,
          CLEAR_COMMAND_STR,
          EXIT_COMMAND_STR,
          GET_COMMAND_STR,
          HELP_COMMAND_STR,
          LIST_COMMAND_STR,
          PUT_COMMAND_STR,
          RM_COMMAND_STR, 
      })
{
}
          
bool AzureCloudStorageService::connect_to_azure(const utility::string_t &account_name, 
    const utility::string_t &access_key, const utility::string_t &endpoint, 
    bool use_https, bool use_dev_storage)
{
    if (!use_dev_storage && access_key.empty()) {
        return false;
    }

    // Initialize the storage account
#if 1
    if (use_dev_storage) {
        // If you want to use a development storage account, please read this article: 
        // Using the Azure Storage Emulator for Development and Testing
        // http://msdn.microsoft.com/en-us/library/azure/hh403989.aspx
        storage_account_ = azure::storage::cloud_storage_account::development_storage_account();
    } else {
        try {
            azure::storage::storage_credentials credential(account_name, access_key);
            storage_account_ = azure::storage::cloud_storage_account(credential, endpoint, use_https);
        } catch (...) {
            return false;
        }
    }
#else
    // The workflow of parse:
    //   1. parse_devstore_settings
    //   2. parse_defaults_settings
    //   3. parse_explicit_settings
    // In cloud_storage_account.cpp, we can see all the valid setting strings.
    utility::string_t connection_string;
    if (use_dev_storage) {
        connection_string = U("UseDevelopmentStorage=true;DevelopmentStorageProxyUri=;");
    } else {
        connection_string =
            utility::string_t(U("DefaultEndpointsProtocol=")) + (use_https ? U("https;") : U("http;")) +
            U("AccountName=") + account_name + U(";") +
            U("AccountKey=") + access_key + U(";") +
            U("EndpointSuffix=") + endpoint + U(";");
    }

    try {
        storage_account_ = azure::storage::cloud_storage_account::parse(connection_string);
    } catch (...) {
        return false;
    }
#endif

    return storage_account_.is_initialized();
}

bool AzureCloudStorageService::initialize(const AzureStorageAccountOptions &storage_account_options)
{
    // ??? What if we regenerate one of the access key?
    if (!connect_to_azure(storage_account_options.account_name, storage_account_options.primary_access_key,
        storage_account_options.endpoint_suffix, storage_account_options.use_https, storage_account_options.use_dev_storage) &&
        !connect_to_azure(storage_account_options.account_name, storage_account_options.secondary_access_key,
        storage_account_options.endpoint_suffix, storage_account_options.use_https, storage_account_options.use_dev_storage)) {
        ucerr << U("Failed to establish connection with azure!\n");
        return false;
    }

    // Initialize blob client
#if 0
    azure::storage::blob_request_options blob_req_options;
    blob_req_options.set_stream_read_size_in_bytes(1024 * 1024);
    blob_req_options.set_stream_write_size_in_bytes(1024 * 1024 * 4);
    blob_req_options.set_server_timeout(std::chrono::seconds(5));

    blob_client_ = storage_account_.create_cloud_blob_client(blob_req_options);
#else
    blob_client_ = storage_account_.create_cloud_blob_client();
#endif

    return true;
}

std::shared_ptr<Command> AzureCloudStorageService::get_command(const utility::string_t &command)
{
    auto command_it = command_dispatcher_.find(command);
    if (command_it != command_dispatcher_.end()) {
        return command_it->second;
    } else {
        //assert(available_commands_.count(command));
        if (command == CD_COMMAND_STR) {
            command_dispatcher_[command].reset(new CdCommand);
        } else if (command == CLEAR_COMMAND_STR) {
            command_dispatcher_[command].reset(new ClearCommand);
        } else if (command == EXIT_COMMAND_STR) {
            command_dispatcher_[command].reset(new ExitCommand);
        } else if (command == GET_COMMAND_STR) {
            command_dispatcher_[command].reset(new GetCommand);
        } else if (command == HELP_COMMAND_STR) {
            command_dispatcher_[command].reset(new HelpCommand);
        } else if (command == LIST_COMMAND_STR) {
            command_dispatcher_[command].reset(new ListCommand);
        } else if (command == PUT_COMMAND_STR) {
            command_dispatcher_[command].reset(new PutCommand);
        } else if (command == RM_COMMAND_STR) {
            command_dispatcher_[command].reset(new RmCommand);
        } else {
            std::basic_ostringstream<utility::string_t::value_type> oss;
            oss << U("Unknown command: \"") << command << U("\". Type \"")
                << HELP_COMMAND_STR << U("\" to get a list of available commands.");
            throw oss.str();
        }

        return command_dispatcher_[command];
    }
}

void AzureCloudStorageService::parse_command_and_dispatch()
{
    utility::string_t cmdline;
    std::vector<utility::string_t> vargs;

    DIVIDING_LINE('-');
    ucout << U("Welcome to azure storage service monitor!\n")
        << U("Type \"") << HELP_COMMAND_STR << U("\" to get a list of all available commands.\nType \"")
        << HELP_COMMAND_STR << U(" [command]\" to learn the usage of given command.\n");
    DIVIDING_LINE('-');

    while (true) {
        if (current_container_.is_valid()) {
            ucout << current_container_.name();
        }
        ucout << U("> ");
        
        if (!std::getline(ucin, cmdline)) {
            ucerr << U("Failed to read user input commands.\n");
            break;
        }

        if (SplitArgsEx(cmdline, vargs) < 1) {
            continue;
        }

        try {
            std::shared_ptr<Command> command = get_command(vargs[0]);

            // Now, erase the command itself and parse the following arguments.
            vargs.erase(vargs.begin());

            try {
                boost::progress_timer t;

                if (command->parse(vargs)) {
                    if (!command->run(this)) {
                        break;
                    }
                }
            } catch (const azure::storage::storage_exception &e) {
                ucerr << storage_exception_to_string_t(e) << U('\n');
            } catch (const std::exception &e) {
                std::cerr << "exception: " << e.what() << '\n';
            } catch (...) {
                ucerr << U("Unknown exception!\n");
            }
        } catch (const utility::string_t &err_msg) {
            ucerr << err_msg << std::endl;
        }
    }
}

utility::string_t AzureCloudStorageService::storage_exception_to_string_t(const azure::storage::storage_exception &e)
{
    utility::string_t err_msg = U("storage_exception: ");

    auto extended_err_msg = e.result().extended_error().message();
    if (extended_err_msg.empty()) {
        err_msg += utility::conversions::to_string_t(e.what());
    } else {
        err_msg += extended_err_msg;
    }

    return err_msg;
}

int AzureCloudStorageService::run(const AzureStorageAccountOptions &storage_account_options)
{
    if (!initialize(storage_account_options)) {
        return EXIT_FAILURE;
    }
    
    parse_command_and_dispatch();
    return EXIT_SUCCESS;
}
