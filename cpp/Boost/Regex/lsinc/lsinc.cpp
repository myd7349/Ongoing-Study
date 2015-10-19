// 2015-10-19T14:16+08:00
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include <boost/regex.hpp>

#include "../../../join.hpp"
#include "../../../read_stream.hpp"


std::vector<std::string> get_included_headers(const std::string &file)
{
    std::vector<std::string> headers;

    std::ifstream fs(file);
    if (!fs)
        return headers;

    auto lines = read_stream(fs);
    auto contents = join(lines.cbegin(), lines.cend(), "");

    fs.close();

    const char *include_re = R"(#[ \t]*include[ \t]+(".+?"|<.+?>)[ \t]*\n)";
    boost::regex pattern(include_re);

    boost::regex_iterator<std::string::const_iterator> rit(contents.cbegin(),
                                                           contents.cend(),
                                                           pattern),
                                                        rit_end;
    std::for_each(rit, rit_end,
        [&headers] (const decltype(rit)::value_type &match)
        {
            headers.push_back(match[1].str());
        });

    return headers;
}

int main(int argc, char *argv[])
{
    auto headers = get_included_headers(argc < 2 ? __FILE__ : argv[1]);

    for (auto h : headers)
        std::cout << h << std::endl;

    return 0;
}
