// 2015-03-12T13:32+08:00
#ifndef RM_COMMAND_H_
#define RM_COMMAND_H_

#include "container_command.h"

#define RM_COMMAND_STR U("rm")

class RmCommand : public ContainerCommand {
public:
    RmCommand();

    virtual bool parse(const std::vector<utility::string_t> &vargs);
    virtual bool run(AzureCloudStorageService *storage_service);
    virtual void help() const;
};

#endif // RM_COMMAND_H_