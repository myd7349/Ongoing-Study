// 2015-01-29T09:16+08:00

#ifndef COMMAND_PARSER_H_
#define COMMAND_PARSER_H_

#include <vector>

#include <wascore/basic_types.h>

namespace azure {
namespace storage {
class cloud_storage_account;
}
}

class Command {
public:
    virtual ~Command() {}
    virtual bool parse(const std::vector<utility::string_t> &vargs) = 0;
    virtual bool run(azure::storage::cloud_storage_account &storage_account) = 0;
};

#endif // COMMAND_PARSER_H_
