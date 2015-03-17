// 2015-03-17T10:18+08:00
// My test environment:
// OS: Win7 x64 with SP1(Chinese Simplified)
// IDE: VS2013 with Update 2
// via: NuGet
// Configuration: Release Win32
//
// https://github.com/Azure/azure-storage-cpp/issues/6
#include <was/storage_account.h>

#ifdef _MSC_VER
# pragma comment(lib, "cpprest120_2_3.lib")
# pragma comment(lib, "wastorage.lib")
#endif

int wmain(int argc, wchar_t *argv[])
{
    utility::string_t account_name = U("devstoreaccount1");
    utility::string_t access_key =
        U("Eby8vdM02xNOcqFlqUwJPLlmEtlCDXJ1OUzFT50uSRZ6IFsuFq2UVErCz4I6tq/K1SZFPTOtr/KBHBeksoGMGw==");
    utility::string_t endpoint = U("core.chinacloudapi.cn");
    bool use_https = false;

    azure::storage::cloud_storage_account storage_account;

#if 0
    azure::storage::storage_credentials credentials(account_name, access_key);

    storage_account = azure::storage::cloud_storage_account(credentials, endpoint, use_https);
#else
    utility::string_t connection_string = 
        utility::string_t(U("DefaultEndpointsProtocol=")) + (use_https ? U("https;") : U("http;")) +
        U("AccountName=") + account_name + U(";") +
        U("AccountKey=") + access_key + U(";") +
        U("EndpointSuffix=") + endpoint + U(";");

    storage_account = azure::storage::cloud_storage_account::parse(connection_string);
#endif

    return 0;
}
