// 2015-01-29T16:44+08:00
#ifndef LIST_COMMAND_H_
#define LIST_COMMAND_H_

#include "../command.h"

#define LIST_COMMAND_STR U("list")

class ListCommand : public Command {
public:
    ListCommand();

    virtual bool parse(const std::vector<utility::string_t> &vargs);
    virtual bool run(AzureCloudStorageService *storage_service);
    virtual void help() const;

private:
    utility::string_t container_name_;
};

#endif // LIST_COMMAND_H_
