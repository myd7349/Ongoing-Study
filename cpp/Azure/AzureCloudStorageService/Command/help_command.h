// 2015-01-30T11:45+08:00

#ifndef HELP_COMMAND_H_
#define HELP_COMMAND_H_

#include "command.h"

#define HELP_COMMAND_STR U("help")

class HelpCommand : public Command {
public:
    virtual bool parse(const std::vector<utility::string_t> &vargs);
    virtual bool run(azure::storage::cloud_storage_account &/*storage_account*/);
};

#endif // HELP_COMMAND_H_
