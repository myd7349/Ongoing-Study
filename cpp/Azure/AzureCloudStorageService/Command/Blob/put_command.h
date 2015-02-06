// 2015-02-04T15:52+08:00

#ifndef PUT_COMMAND_H_
#define PUT_COMMAND_H_

#include "container_command.h"

#define PUT_COMMAND_STR U("put")

class PutCommand : public ContainerCommand {
public:
    PutCommand();

    virtual bool parse(const std::vector<utility::string_t> &vargs);
    virtual bool run(AzureCloudStorageService *storage_service);
    virtual void help() const;

private:
    utility::string_t blob_name_;
    utility::string_t local_file_name_;
};

#endif // PUT_COMMAND_H_