// 2015-02-03T14:58+08:00

#ifndef CLEAR_COMMAND_H_
#define CLEAR_COMMAND_H_

#include "command.h"

#define CLEAR_COMMAND_STR U("clear")

class ClearCommand : public Command {
public:
    virtual bool parse(const std::vector<utility::string_t> &vargs);
    virtual bool run(AzureCloudStorageService *storage_service);
    virtual void help() const;
};

#endif // CLEAR_COMMAND_H_