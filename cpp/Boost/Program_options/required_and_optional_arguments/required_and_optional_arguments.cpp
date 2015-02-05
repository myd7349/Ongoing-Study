// 2015-02-05T15:10+08:00
// When I was using Boost.Program_options to parse command line arguments
// today, I run into one question: How to mark an argument as a required one?
// Then, I found a similar question on stackoverflow:
// [Required and Optional Arguments Using Boost Library Program Options](http://stackoverflow.com/questions/5395503/required-and-optional-arguments-using-boost-library-program-options)
// Now, let's try it out.

#include <iostream>
#include <string>
#include <vector>

#include <boost/program_options.hpp>

#include "../../../common.h"
#include "../../../dividing_lines.h"

namespace po = boost::program_options;

namespace situation_one {
void test()
{
    std::string output_filename;

    po::options_description options_desc("Options");
    options_desc.add_options()
        // By calling "required", we make this option a required one.
        ("out,o", po::value<std::string>(&output_filename)->required(), "Output file name")
        ;

    po::variables_map args_map;

    std::vector<std::string> vargs{ "-o", "a.out" };

    // Test 0
    DIVIDING_LINE('+', 40);
    po::store(po::command_line_parser(vargs).options(options_desc).run(), args_map);
    po::notify(args_map);
    std::cout << output_filename << std::endl;

    // Test 1
    DIVIDING_LINE('+', 40);
    vargs.clear();
    args_map.clear();
    try {
        po::store(po::command_line_parser(vargs).options(options_desc).run(), args_map);
        po::notify(args_map);
        std::cout << output_filename << std::endl;
    } catch (const po::required_option &e) {
        std::cerr << "boost::program_options::required_option: " << e.what() << '\n';
    }
}
}

namespace situation_two {
void test()
{
    po::options_description options_desc("Options");
    options_desc.add_options()
        ("help,h", "Produce help message")
        ("out,o", po::value<std::string>()->required(), "Output file name")
        ;

    po::variables_map args_map;
    std::vector<std::string> vargs;

    // Test 0
    DIVIDING_LINE('+', 40);
    vargs = { "-h" };
    po::store(po::command_line_parser(vargs).options(options_desc).run(), args_map);
    try {
        if (args_map.count("help") > 0) {
            std::cout << options_desc << std::endl;
        } else {
            po::notify(args_map);
        }
    } catch (const po::required_option &e) {
    } catch (...) {
    }

    // Test 1
    DIVIDING_LINE('+', 40);
    vargs = { "--out=hello.exe" };
    args_map.clear();
    po::store(po::command_line_parser(vargs).options(options_desc).run(), args_map);
    po::notify(args_map);
    std::cout << args_map["out"].as<std::string>() << std::endl;
}
}

int main()
{
    DIVIDING_LINE('=');
    situation_one::test();

    DIVIDING_LINE('=');
    situation_two::test();

    PAUSE();
    return 0;
}