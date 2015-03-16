// 2015-01-29T16:44+08:00
#ifndef LIST_COMMAND_H_
#define LIST_COMMAND_H_

#include "container_command.h"

#define LIST_COMMAND_STR U("list")

namespace azure {
namespace storage {
class cloud_blob_client;
class cloud_blob_container;
}
}

class ListCommand : public ContainerCommand {
public:
    virtual bool parse(const std::vector<utility::string_t> &vargs);
    virtual bool run(AzureCloudStorageService *storage_service);
    virtual void help() const;

    static std::vector<utility::string_t> get_container_list(azure::storage::cloud_blob_client &blob_client);
    static std::vector<utility::string_t> get_blob_list(azure::storage::cloud_blob_client &blob_client,
        const utility::string_t &container_name, const utility::string_t &prefix = U(""), bool short_name = false);
    static std::vector<utility::string_t> get_blob_list(azure::storage::cloud_blob_container &blob_container, 
        const utility::string_t &prefix = U(""), bool short_name = false);
};

#endif // LIST_COMMAND_H_
