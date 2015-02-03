// 2015-01-29T09:16+08:00

#ifndef COMMAND_H_
#define COMMAND_H_

#include <vector>

#include <boost/program_options.hpp>

#include <wascore/basic_types.h>

class AzureCloudStorageService;

class Command {
public:
    Command();
    virtual ~Command() {}

    virtual bool parse(const std::vector<utility::string_t> &vargs) = 0;
    virtual bool run(AzureCloudStorageService *storage_service) = 0;
    virtual void help() const;

protected:
    void notify_err(const char *what, const utility::string_t &command);

    boost::program_options::options_description options_desc_;
};

#endif // COMMAND_PARSER_H_
