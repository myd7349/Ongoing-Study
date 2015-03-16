// 2015-03-12T13:33+08:00

#include "rm_command.h"

#include "../../azure_cloud_storage_service.h"

void delete_container(azure::storage::cloud_blob_container &container)
{
    container.delete_container_if_exists();
}

void delete_block_blob(azure::storage::cloud_blob_container &container, 
    const utility::string_t &blob_name)
{
    auto blob = container.get_block_blob_reference(blob_name);
    blob.delete_blob_if_exists();
}

RmCommand::RmCommand()
{
}

bool RmCommand::parse(const std::vector<utility::string_t> &vargs)
{
    return parse_helper(vargs, RM_COMMAND_STR);
}

bool RmCommand::run(AzureCloudStorageService *storage_service)
{
    if (container_name_.empty()) {
        if (storage_service->current_container_.is_valid()) {
        } else {
        }
    } else {
    }
    return true;
}

void RmCommand::help() const
{
}
