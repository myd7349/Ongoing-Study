// 2015-02-04T15:54+08:00

#ifndef GET_COMMAND_H_
#define GET_COMMAND_H_

#include "../command.h"

#define GET_COMMAND_STR U("get")

class GetCommand : public Command {
public:
    virtual bool parse(const std::vector<utility::string_t> &vargs);
    virtual bool run(AzureCloudStorageService *storage_service);
    virtual void help() const;
};

#endif // GET_COMMAND_H_