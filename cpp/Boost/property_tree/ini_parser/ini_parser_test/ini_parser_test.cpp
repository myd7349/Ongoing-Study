// 2015-01-22T16:40+08:00
// An example demonstrating how to parse *.ini files with 
// Boost.property_tree.ini_parser.
// Boost.property_tree can also be used to parse JSON, XML files.
// Please read the Boost library documentation for more details. 

#include <iostream>
#include <string>

#include <boost/property_tree/ini_parser.hpp>

#include "../../../../common.h"

namespace Cfg = boost::property_tree;

int main()
{
    // Parse the configuration file and fetch out information we need.
    Cfg::basic_ptree<std::string, std::string> cfg;
    try {
        Cfg::read_ini("example.configuration", cfg);
    } catch (const Cfg::ini_parser_error &e) {
        RETURN_ON_FAILURE_MSG("ini_parser_error");
    }

    try {
        std::cout << cfg.get<std::string>("ACCOUNT.account_name") << std::endl;
        std::cout << cfg.get<std::string>("ACCOUNT.primary_access_key") << std::endl;
        std::cout << cfg.get<std::string>("ACCOUNT.secondary_access_key") << std::endl;
        std::cout << cfg.get<std::string>("ACCOUNT.end_point") << std::endl;
        std::cout << cfg.get<bool>("ACCOUNT.use_https") << std::endl;
        std::cout << cfg.get<bool>("ACCOUNT.use_dev_account") << std::endl;
    } catch (const Cfg::ptree_bad_path &e) {
        RETURN_ON_FAILURE_MSG("ptree_bad_path");
    } catch (const Cfg::ptree_bad_data &e) {
        RETURN_ON_FAILURE_MSG("ptree_bad_data");
    } catch (const std::exception &e) {
        RETURN_ON_FAILURE_MSG("exception");
    }

    PAUSE();
    return 0;
}