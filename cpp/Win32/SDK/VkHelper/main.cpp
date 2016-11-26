// 2016-11-25T09:52+08:00
#include <iostream>

#include "../../../common.h"
#include "../../../dividing_lines.h"
#include "KeySequence.h"

#define PRINT_VK_NAME(vk) std::wcout << #vk << L"(" << vk << L"): " << VkUtils::GetVkName(vk) << std::endl

#define PRINT_KEY_SEQ(keySeq) std::wcout << #keySeq << L": " << keySeq.ToString() << std::endl

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
    PRINT_VK_NAME(VkUtils::GetVkCode(L" myd "));

    DIVIDING_LINE_1('>');

    PRINT_KEY_SEQ(KeySequence(VK_F1));
    PRINT_KEY_SEQ(KeySequence('A', HOTKEYF_CONTROL));
    PRINT_KEY_SEQ(KeySequence('F', HOTKEYF_CONTROL | HOTKEYF_SHIFT | HOTKEYF_ALT));

    return 0;
}
