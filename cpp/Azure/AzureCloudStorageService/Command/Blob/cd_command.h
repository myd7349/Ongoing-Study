// 2015-02-03T08:39+08:00

#ifndef CD_COMMAND_H_
#define CD_COMMAND_H_

#include "../command.h"

#define CD_COMMAND_STR U("cd")

class CdCommand : public Command {
public:
    virtual bool parse(const std::vector<utility::string_t> &vargs);
    virtual bool run(AzureCloudStorageService *storage_service);
    virtual void help() const;
};

#endif // CD_COMMAND_H_
