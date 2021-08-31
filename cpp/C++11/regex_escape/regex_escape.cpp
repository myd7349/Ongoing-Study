#include <algorithm>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <vector>

#include "flushinp.hpp"
#include "join.hpp"


std::string RegexEscape(const std::string &str)
{
    const std::regex esc("[.^$|()\\[\\]{}*+?\\\\]");
    const std::string rep("\\\\&");
    return std::regex_replace(str, esc, rep,
        std::regex_constants::match_default | std::regex_constants::format_sed);
}


template <typename InputIt>
std::string BuildGroup(InputIt first, InputIt last, bool escape)
{
    if (escape)
    {
        std::vector<std::string> escapedStrings(first, last);
        std::transform(escapedStrings.cbegin(), escapedStrings.cend(), escapedStrings.begin(), RegexEscape);
        return join(escapedStrings.cbegin(), escapedStrings.cend(), '|');
    }
    else
    {
        return join(first, last, '|');
    }
}


int main()
{
    std::string knownStrings[] { "a|b|c", "d*e*f", "(ghi)", "jkl", "[cppreference](https://en.cppreference.com/w/)" };

    std::cout << "Known strings:\n";
    std::copy(std::begin(knownStrings), std::end(knownStrings), std::ostream_iterator<std::string>(std::cout, "\n"));

    std::vector<std::string> escapedKnownStrings(std::begin(knownStrings), std::end(knownStrings));
    std::transform(escapedKnownStrings.cbegin(), escapedKnownStrings.cend(), escapedKnownStrings.begin(), RegexEscape);

    std::cout << "Known strings(escaped):\n";
    std::copy(escapedKnownStrings.cbegin(), escapedKnownStrings.cend(), std::ostream_iterator<std::string>(std::cout, "\n"));

    std::cout << "Now let's play a game!\nFirst tell me do you want to escape the regex? (true/false) > ";
    bool escape = true;
    std::cin >> std::boolalpha >> escape;
    if (!std::cin)
    {
        std::cout << "I don't understand your input. I will assume you'd like to escape the regex.\n";
        std::cin.clear();
    }
    else
    {
        std::cout << "OK! Your answer is: " << std::boolalpha << escape << std::endl;
    }
    flushinp(std::cin, '\n');

    std::string knownStringsRE = BuildGroup(std::begin(knownStrings), std::end(knownStrings), escape);
    std::cout << "The finally RE we got: " << knownStringsRE << std::endl;

    std::regex re(knownStringsRE);

    std::string input;
    std::cout << "> ";
    while (std::getline(std::cin, input))
    {
        std::smatch results;
        if (!std::regex_match(input.cbegin(), input.cend(), results, re))
            std::cout << "The input doesn't match with any known strings.\n";
        else
            std::cout << "Found a match.\n";

        std::cout << "> ";
    }

    return 0;
}


// References:
// [How to escape a string for use in Boost Regex](https://stackoverflow.com/questions/1252992/how-to-escape-a-string-for-use-in-boost-regex)
