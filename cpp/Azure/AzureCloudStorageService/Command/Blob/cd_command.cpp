// 2015-02-03T08:39+08:00

#include "cd_command.h"

#include <cassert>

#include "../../azure_cloud_storage_service.h"
#include "list_command.h"

bool CdCommand::parse(const std::vector<utility::string_t> &vargs)
{
    return parse_helper(vargs, CD_COMMAND_STR);
}

bool CdCommand::run(AzureCloudStorageService *storage_service)
{
    assert(storage_service != nullptr);

    if (container_name_.empty()) {
        if (storage_service->current_container_.is_valid()) {
            ucout << storage_service->current_container_.name() << U('\n');
        }
    } else if (U("~") == container_name_) {
        //storage_service->current_container_ = storage_service->blob_client_.get_root_container_reference(); // ???
        storage_service->current_container_ = azure::storage::cloud_blob_container();
    } else {
        auto container = storage_service->blob_client_.get_container_reference(container_name_);
        if (!container.exists()) {
            ucerr << U("Container \"") << container_name_ << U("\" doesn't exist. Type \"")
                << LIST_COMMAND_STR << U(" ~\" to get a list of existing containers.\n");
        } else {
            storage_service->current_container_ = container;
        }
    }

    return true;
}

void CdCommand::help() const
{
    ucout << U("Change the current container.\nUsage: ") << CD_COMMAND_STR << U(" [container]\n");
    Command::help();
}