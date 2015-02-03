// 2015-01-28T08:46+08:00

#ifndef AZURE_CLOUD_STORAGE_SERVICE_H_
#define AZURE_CLOUD_STORAGE_SERVICE_H_

#include <memory>
#include <set>
#include <unordered_map>

#include <boost/core/noncopyable.hpp>

#include <wascore/basic_types.h>
#include <was/blob.h>
#include <was/storage_account.h>

struct AzureStorageAccountOptions {
    utility::string_t account_name;
    utility::string_t primary_access_key;
    utility::string_t secondary_access_key;
    utility::string_t end_point_suffix = U("core.windows.net");
    bool use_https = false;
    bool use_dev_storage = false;
};

class Command;

// Azure cloud storage service wrapper class.
class AzureCloudStorageService : public boost::noncopyable {
    friend class HelpCommand;
    friend class ListCommand;
public:
    AzureCloudStorageService();
    int run(const AzureStorageAccountOptions &storage_account_options);

protected:
    bool initialize(const AzureStorageAccountOptions &storage_account_options);
    std::shared_ptr<Command> get_command(const utility::string_t &command);
    void parse_command_and_dispatch();

private:
    azure::storage::cloud_storage_account storage_account_;
    azure::storage::cloud_blob_client blob_client_;
    utility::string_t current_container_name_;
    std::set<utility::string_t> available_commands_;
    std::unordered_map<utility::string_t, std::shared_ptr<Command>> command_dispatcher_;
};

#endif // AZURE_CLOUD_STORAGE_SERVICE_H_
