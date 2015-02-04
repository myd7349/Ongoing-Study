// 2015-02-04T15:54+08:00

#include "get_command.h"

bool GetCommand::parse(const std::vector<utility::string_t> &vargs)
{
    return true;
}

bool GetCommand::run(AzureCloudStorageService *storage_service)
{
    return true;
}

void GetCommand::help() const
{

}