// 2015-01-29T16:44+08:00

#include "list_command.h"

#include <cassert>

#include <was/blob.h>
#include <was/storage_account.h>

#include "../../azure_cloud_storage_service.h"

ListCommand::ListCommand()
{
    options_desc_.add_options()
        ("container,c", boost::program_options::wvalue<utility::string_t>(&container_name_), "Specify the target container name")
        ;
}

bool ListCommand::parse(const std::vector<utility::string_t> &vargs)
{
    container_name_.clear();

    boost::program_options::positional_options_description container_name_option;
    container_name_option.add("container", 1);

    boost::program_options::variables_map args_map;

    try {
        using CharT = utility::string_t::traits_type::char_type;
        //using CharT = typename utility::string_t::value_type;

        boost::program_options::store(boost::program_options::basic_command_line_parser<CharT>(vargs).
            options(options_desc_).positional(container_name_option).run(), args_map);
        boost::program_options::notify(args_map);

        return true;
    } catch (const std::exception &e) {
        notify_err(e.what(), LIST_COMMAND_STR);
        return false;
    }
}

bool ListCommand::run(AzureCloudStorageService *storage_service)
{
    return true;
}

void ListCommand::help() const
{
    ucout << U("Usage: ") << LIST_COMMAND_STR << U(" [container]\n");
    Command::help();
}
