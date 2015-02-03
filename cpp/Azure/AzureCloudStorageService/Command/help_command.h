// 2015-01-30T11:45+08:00

#ifndef HELP_COMMAND_H_
#define HELP_COMMAND_H_

#include "command.h"

#define HELP_COMMAND_STR U("help")

class HelpCommand : public Command {
public:
    HelpCommand();

    virtual bool parse(const std::vector<utility::string_t> &vargs);
    virtual bool run(AzureCloudStorageService *storage_service);
    virtual void help() const;

private:
    utility::string_t command_;
    std::vector<utility::string_t> sorted_commands_;
};

#endif // HELP_COMMAND_H_
