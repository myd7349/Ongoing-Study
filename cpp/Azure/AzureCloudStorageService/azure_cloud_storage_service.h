// 2015-01-28T08:46+08:00

#ifndef AZURE_CLOUD_STORAGE_SERVICE_H_
#define AZURE_CLOUD_STORAGE_SERVICE_H_

#include <algorithm>
#include <iterator>
#include <memory>
#include <set>
#include <unordered_map>

#include <boost/core/noncopyable.hpp>

#include <was/blob.h>
#include <was/storage_account.h>

struct AzureStorageAccountOptions {
    utility::string_t account_name;
    utility::string_t primary_access_key;
    utility::string_t secondary_access_key;
    utility::string_t endpoint_suffix = U("core.windows.net");
    bool use_https = false;
    bool use_dev_storage = false;
};

class Command;

// Azure cloud storage service wrapper class.
class AzureCloudStorageService : public boost::noncopyable {
    friend class CdCommand;
    friend class GetCommand;
    friend class HelpCommand;
    friend class ListCommand;
    friend class PutCommand;
public:
    AzureCloudStorageService();
    int run(const AzureStorageAccountOptions &storage_account_options);

protected:
    bool connect_to_azure(const utility::string_t &account_name, const utility::string_t &access_key,
        const utility::string_t &endpoint, bool use_https, bool use_dev_storage);
    bool initialize(const AzureStorageAccountOptions &storage_account_options);
    std::shared_ptr<Command> get_command(const utility::string_t &command);
    void parse_command_and_dispatch();

private:
    azure::storage::cloud_storage_account storage_account_;
    azure::storage::cloud_blob_client blob_client_;
    azure::storage::cloud_blob_container current_container_;
    std::set<utility::string_t> available_commands_;
    std::unordered_map<utility::string_t, std::shared_ptr<Command>> command_dispatcher_;
};

template <typename Container>
void DumpLineByLine(const Container &c)
{
    std::copy(c.cbegin(), c.cend(),
        std::ostream_iterator<utility::string_t, utility::string_t::value_type>(ucout, U("\n")));
}

void DumpAzureStorageError(const azure::storage::storage_exception &e);

#endif // AZURE_CLOUD_STORAGE_SERVICE_H_
