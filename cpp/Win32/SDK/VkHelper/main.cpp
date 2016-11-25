// 2016-11-25T09:52+08:00
#include <iostream>

#include "../../../common.h"
#include "../../../dividing_lines.h"

#include "Vkhelper.h"

#define PRINT_VK_NAME(vk) std::wcout << #vk << ": " << VkUtils::GetVkName(vk) << std::endl

#include "../../../strutils.hpp"

int main()
{
    PRINT_VK_NAME(VK_F1);
    PRINT_VK_NAME(VK_CONTROL);
    PRINT_VK_NAME(VK_LCONTROL);
    PRINT_VK_NAME(VK_MENU);
    PRINT_VK_NAME(VK_SHIFT);
    PRINT_VK_NAME(VK_NUMPAD0);

    DIVIDING_LINE_1('-');

    PRINT_VK_NAME(VkUtils::GetVkCode(L"Ctrl"));
    PRINT_VK_NAME(VkUtils::GetVkCode(L"alt"));
    PRINT_VK_NAME(VkUtils::GetVkCode(L"f12"));
    PRINT_VK_NAME(VkUtils::GetVkCode(L"num 0"));
    PRINT_VK_NAME(VkUtils::GetVkCode(L"0"));

    DIVIDING_LINE_1('+');

    PRINT_VK_NAME(VkUtils::GetVkCode(L" a "));
    PRINT_VK_NAME(VkUtils::GetVkCode(L" B "));
    PRINT_VK_NAME(VkUtils::GetVkCode(L" cTrL "));

    return 0;
}
