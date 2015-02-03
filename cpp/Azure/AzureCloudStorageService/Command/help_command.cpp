// 2015-01-30T11:45+08:00

#include "help_command.h"

bool HelpCommand::parse(const std::vector<utility::string_t> &vargs)
{
    return true;
}

bool HelpCommand::run(azure::storage::cloud_storage_account &/*storage_account*/)
{
    return true;
}
