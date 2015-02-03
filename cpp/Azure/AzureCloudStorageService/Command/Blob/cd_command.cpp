// 2015-02-03T08:39+08:00

#include "cd_command.h"

bool CdCommand::parse(const std::vector<utility::string_t> &vargs)
{
    return false;
}

bool CdCommand::run(AzureCloudStorageService *storage_service)
{
    return true;
}

void CdCommand::help() const
{

}