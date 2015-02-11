// 2015-02-04T15:54+08:00

#ifndef GET_COMMAND_H_
#define GET_COMMAND_H_

#include "container_command.h"

#define GET_COMMAND_STR U("get")

class GetCommand : public ContainerCommand {
public:
    GetCommand();

    virtual bool parse(const std::vector<utility::string_t> &vargs);
    virtual bool run(AzureCloudStorageService *storage_service);
    virtual void help() const;

private:
    utility::string_t blob_name_;
    utility::string_t target_local_file_name_;
    utility::size64_t size_;
};

#endif // GET_COMMAND_H_