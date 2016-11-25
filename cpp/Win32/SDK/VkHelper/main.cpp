// 2016-11-25T09:52+08:00
#include <iostream>

#include "Vkhelper.h"

#define PRINT_VK_NAME(vk) std::wcout << #vk << ": " << VkUtils::GetVkName(vk) << std::endl

int main()
{
    PRINT_VK_NAME(VK_F1);
    PRINT_VK_NAME(VK_CONTROL);
    PRINT_VK_NAME(VK_LCONTROL);
    PRINT_VK_NAME(VK_MENU);
    PRINT_VK_NAME(VK_SHIFT);
    PRINT_VK_NAME(VK_NUMPAD0);

    return 0;
}
