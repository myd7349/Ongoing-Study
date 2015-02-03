// 2015-02-03T14:58+08:00

#include "clear_command.h"

#include <cstdlib>

bool ClearCommand::parse(const std::vector<utility::string_t> &vargs)
{
    return true;
}

bool ClearCommand::run(AzureCloudStorageService *storage_service)
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
    return true;
}

void ClearCommand::help() const
{
    ucout << U("Clear the screen.\n");
}