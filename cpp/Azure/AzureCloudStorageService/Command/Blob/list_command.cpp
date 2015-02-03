// 2015-01-29T16:44+08:00

#include "list_command.h"

#include <cassert>
#include <exception>
#include <iostream>

#include <boost/program_options.hpp>

#include <was/blob.h>
#include <was/storage_account.h>

namespace Opt = boost::program_options;

bool ListCommand::parse(const std::vector<utility::string_t> &vargs)
{
    Opt::options_description list_options("Options");
    list_options.add_options()
        ("container,c", Opt::wvalue<utility::string_t>(&container_name_), "")
        ;

    Opt::positional_options_description container_name_option;
    container_name_option.add("container", 1);

    Opt::variables_map args_map;

    try {
        using CharT = utility::string_t::traits_type::char_type;
        //using CharT = typename utility::string_t::value_type;

        Opt::store(Opt::basic_command_line_parser<CharT>(vargs).
            options(list_options).positional(container_name_option).run(), args_map);
        Opt::notify(args_map);

        container_name_provided_ = args_map.count("container") > 0;

        return true;
    } catch (const std::exception &e) {
        ucerr << U("Failed to parse \"") << LIST_COMMAND_STR << U("\" command: ");
        std::cerr << e.what() << '\n';
        ucerr << U("Usage: ") << LIST_COMMAND_STR << U(" [container]\n");
        std::cerr << list_options << '\n';
        return false;
    }
}

bool ListCommand::run(azure::storage::cloud_storage_account &storage_account)
{
    assert(storage_account.is_initialized());
    return true;
}
