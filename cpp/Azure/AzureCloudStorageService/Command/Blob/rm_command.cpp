// 2015-03-12T13:33+08:00

#include "rm_command.h"

RmCommand::RmCommand()
{

}

bool RmCommand::parse(const std::vector<utility::string_t> &vargs)
{
    return true;
}

bool RmCommand::run(AzureCloudStorageService *storage_service)
{
    return true;
}

void RmCommand::help() const
{

}
