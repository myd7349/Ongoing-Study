// 2014-12-17T13:31+08:00

// An example for testing Azure Storage CPP SDK. 
// Several official examples can be found here:
// https://github.com/Azure/azure-storage-cpp/blob/master/Microsoft.WindowsAzure.Storage/samples/

#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>

#include <boost/property_tree/ini_parser.hpp>

#include <was/blob.h>
#include <was/common.h>
#include <was/storage_account.h>
#include <wascore/basic_types.h>

#ifdef _MSC_VER
# ifdef NDEBUG
#  pragma comment(lib, "cpprest120_2_3.lib") // cpprest SDK for VS2013
# else
#  pragma comment(lib, "cpprest120d_2_3.lib") // cpprest SDK for VS2013
# endif

# pragma comment(lib, "wastorage.lib")
#endif

#if !defined(NDEBUG) && defined(_MSC_VER)
# define PAUSE() (std::system("pause")) 
#else
# define PAUSE() (__noop)
#endif

#define RETURN_ON_FAILURE() std::cerr << e.what() << '\n'; PAUSE(); return EXIT_FAILURE

namespace AS = azure::storage;
namespace Cfg = boost::property_tree;

int main(int argc, char *argv[])
{
    // parse the configuration file and fetch out account name, account key, host endpoint
    Cfg::basic_ptree<utility::string_t, utility::string_t> cfg;
    try {
        // The structure of "azure_storage_test.cfg" is described in this example:
        // https://github.com/myd7349/Ongoing-Study/blob/master/python/Azure/azure_storage_test/azure_storage_test.py
        Cfg::read_ini("azure_storage_test.cfg", cfg);
    } catch (const Cfg::ini_parser_error &e) {
        RETURN_ON_FAILURE();
    }

    utility::string_t accountName;
    utility::string_t accountKey;
    // I am using Microsoft Azure China service, so my endpoint is: core.chinacloudapi.cn
    utility::string_t endPoint = U("core.chinacloudapi.cn");

    try {
        accountName = cfg.get<utility::string_t>(U("ACCOUNT.name"));
        accountKey = cfg.get<utility::string_t>(U("ACCOUNT.key"));
        //endPoint = cfg.get<utility::string_t>(U("ACCOUNT.host"));
    } catch (const Cfg::ptree_bad_path &e) {
        RETURN_ON_FAILURE();
    } catch (const Cfg::ptree_bad_data &e) {
        RETURN_ON_FAILURE();
    }

    AS::cloud_storage_account asAccount;

    // initialize the storage account
#if 1
    try {
        AS::storage_credentials credential(accountName, accountKey);
        asAccount = AS::cloud_storage_account(credential, endPoint, true);
    } catch (const std::runtime_error &e) {
        RETURN_ON_FAILURE();
    }
#else
    // The workflow of parse:
    //   1. parse_devstore_settings
    //   2. parse_defaults_settings
    //   3. parse_explicit_settings
    // In cloud_storage_account.cpp, we can see all the valid setting strings.
    utility::string_t connStr = U("DefaultEndpointsProtocol=https;AccountName=")
        + accountName + U(";AccountKey=") + accountKey + U(";EndpointSuffix=") + endPoint;

    try {
        asAccount = AS::cloud_storage_account::parse(connStr);
    } catch (const std::invalid_argument &e) {
        RETURN_ON_FAILURE();
    }
#endif

    AS::cloud_blob_client blobClient = asAccount.create_cloud_blob_client();
    // Caution:
    // A container name must be a valid DNS name. Please read the naming convention described here:
    // http://msdn.microsoft.com/en-us/library/azure/dd135715.aspx
    AS::cloud_blob_container container = blobClient.get_container_reference(U("myd7349"));
    try {
        container.create_if_not_exists();
    } catch (const std::exception &e) {
        RETURN_ON_FAILURE();
    }

    // set access permission
    AS::blob_container_permissions permission;
    permission.set_public_access(AS::blob_container_public_access_type::blob);
    container.upload_permissions(permission);

    PAUSE();
    return EXIT_SUCCESS;
}