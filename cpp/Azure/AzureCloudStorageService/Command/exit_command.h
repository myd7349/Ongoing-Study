// 2015-01-19T17:26+08:00

#ifndef EXIT_COMMAND_H_
#define EXIT_COMMAND_H_

#include "command.h"

#define EXIT_COMMAND_STR U("exit")

class ExitCommand : public Command {
public:
    virtual bool parse(const std::vector<utility::string_t> &/*vargs*/);
    virtual bool run(AzureCloudStorageService */*storage_service*/);
    virtual void help() const;
};

#endif // EXIT_COMMAND_H_
