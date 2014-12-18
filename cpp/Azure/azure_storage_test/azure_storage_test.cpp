// 2014-12-17T13:31+08:00

// An example for testing Azure Storage CPP SDK. 
// Several official examples can be found here:
// https://github.com/Azure/azure-storage-cpp/blob/master/Microsoft.WindowsAzure.Storage/samples/

#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>

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

namespace AS = azure::storage;

int main(int argc, char *argv[])
{
    utility::string_t accountName = U("Your account name here");
    utility::string_t accountKey = U("Your account key here");
    utility::string_t endPoint = U("core.chinacloudapi.cn");

    AS::cloud_storage_account asAccount;

    // initialize the storage account
#if 1
    try {
        AS::storage_credentials credential(accountName, accountKey);
        asAccount = AS::cloud_storage_account(credential, endPoint, true);
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        PAUSE();
        return EXIT_FAILURE;
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
        std::cerr << e.what() << std::endl;
        PAUSE();
        return EXIT_FAILURE;
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
        std::cerr << e.what() << std::endl;
        PAUSE();
        return EXIT_FAILURE;
    }

    // set access permission
    AS::blob_container_permissions permission;
    permission.set_public_access(AS::blob_container_public_access_type::blob);
    container.upload_permissions(permission);

    PAUSE();
    return EXIT_SUCCESS;
}
