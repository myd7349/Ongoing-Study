// 2015-02-04T14:23+08:00

#ifndef CONTAINER_COMMAND_H_
#define CONTAINER_COMMAND_H_

#include "../command.h"

class ContainerCommand : public Command {
public:
    ContainerCommand();

protected:
    bool parse_helper(const std::vector<utility::string_t> &vargs, 
        const utility::string_t &command);

    utility::string_t container_name_;
};

#endif // CONTAINER_COMMAND_H_