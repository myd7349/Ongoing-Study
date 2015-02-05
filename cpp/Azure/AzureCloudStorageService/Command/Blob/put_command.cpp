// 2015-02-04T15:52+08:00

#include "put_command.h"

bool PutCommand::parse(const std::vector<utility::string_t> &vargs)
{
    return true;
}

bool PutCommand::run(AzureCloudStorageService *storage_service)
{
    return true;
}

void PutCommand::help() const
{
}
