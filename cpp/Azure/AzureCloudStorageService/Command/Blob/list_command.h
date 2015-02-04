// 2015-01-29T16:44+08:00
#ifndef LIST_COMMAND_H_
#define LIST_COMMAND_H_

#include "../command.h"

#define LIST_COMMAND_STR U("list")

namespace azure {
namespace storage {
class cloud_blob_client;
class cloud_blob_container;
}
}

class ListCommand : public Command {
public:
    ListCommand();

    virtual bool parse(const std::vector<utility::string_t> &vargs);
    virtual bool run(AzureCloudStorageService *storage_service);
    virtual void help() const;

protected:
    std::vector<utility::string_t> get_container_list(azure::storage::cloud_blob_client &blob_client);
    std::vector<utility::string_t> get_blob_list(azure::storage::cloud_blob_client &blob_client,
        const utility::string_t &container_name);
    std::vector<utility::string_t> get_blob_list(azure::storage::cloud_blob_container &blob_container);

private:
    utility::string_t container_name_;
};

#endif // LIST_COMMAND_H_
