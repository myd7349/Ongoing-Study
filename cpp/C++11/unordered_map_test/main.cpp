// 2016-11-25T14:15+08:00
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>

#include "../../strutils.hpp"


typedef std::unordered_map<std::string,
                           int,
                           StringIHash<char>,
                           std::pointer_to_binary_function<const std::string &, const std::string &, bool>> NameAgeMap;


int main()
{
    NameAgeMap nameAgeMap(
        static_cast<NameAgeMap::size_type>(0),
        NameAgeMap::hasher(),
        std::ptr_fun(StringICompare<char>));
    nameAgeMap["ned stark"] = 45;

    std::cout << nameAgeMap["Ned Stark"] << std::endl;

    return 0;
}

// References:
// Ongoing-Study\cpp\Win32\SDK\VkHelper\VkHelper.cpp