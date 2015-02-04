// 2015-02-04T14:23+08:00

#include "container_command.h"

ContainerCommand::ContainerCommand()
{
    options_desc_.add_options()
        ("container,c", boost::program_options::wvalue<utility::string_t>(&container_name_), "Specify the target container name")
        ;
}

bool ContainerCommand::parse_helper(const std::vector<utility::string_t> &vargs,
    const utility::string_t &command)
{
    container_name_.clear();

    boost::program_options::positional_options_description container_name_option;
    container_name_option.add("container", 1);

    boost::program_options::variables_map args_map;

    try {
        using CharT = utility::string_t::traits_type::char_type;

        boost::program_options::store(boost::program_options::basic_command_line_parser<CharT>(vargs).
            options(options_desc_).positional(container_name_option).run(), args_map);
        boost::program_options::notify(args_map);

        return true;
    } catch (const std::exception &e) {
        notify_err(e.what(), command);
        return false;
    }
}
