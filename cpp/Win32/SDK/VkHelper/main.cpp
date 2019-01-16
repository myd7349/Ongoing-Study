// 2016-11-25T09:52+08:00
#include <iostream>
#include <unordered_set>

#include "../../../common.h"
#include "../../../dividing_lines.h"
#include "AccelTable.hpp"

#define PRINT_VK_NAME(vk) std::wcout << #vk << L"(" << vk << L"): " << VkUtils::GetVkName(vk) << std::endl

#define PRINT_KEY_SEQ(keySeq) std::wcout << #keySeq << L": " << keySeq.ToString(L" + ") << std::endl


const cmd_t ID_COPY = 0;
const cmd_t ID_PASTE = 1;
const cmd_t ID_CUT = 2;
const cmd_t ID_EXIT = 3;


struct Command
{
    cmd_t cmd;
    std::wstring name;
} commands[] =
{
    { ID_COPY, L"Copy" },
    { ID_PASTE, L"Paste" },
    { ID_CUT, L"Cut" },
    { ID_EXIT, L"Exit" }
};


void PrintAccelTable(AccelTable &table)
{
    DIVIDING_LINE_1('~');

    for (const auto &entry : table)
        std::wcout << commands[entry.first].name << L": " << entry.second.ToString() << L'\n';

    DIVIDING_LINE_1('^');
}


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
    PRINT_KEY_SEQ(KeySequence(L'F', HOTKEYF_CONTROL | HOTKEYF_SHIFT | HOTKEYF_ALT));
    PRINT_KEY_SEQ(KeySequence());
    PRINT_KEY_SEQ(KeySequence(VK_F4, false, false, true));

    DIVIDING_LINE_1('.');

    PRINT_KEY_SEQ(KeySequence(L"f12"));
    PRINT_KEY_SEQ(KeySequence(L"ctrl+s"));
    PRINT_KEY_SEQ(KeySequence(L"alt+ctrl+shift+1"));
    PRINT_KEY_SEQ(KeySequence(L"ctrl/shift/alt/F12", L"/"));
    PRINT_KEY_SEQ(KeySequence(L"ctrl+ctrl+s"));
    PRINT_KEY_SEQ(KeySequence(L"ctrl"));
    PRINT_KEY_SEQ(KeySequence(L"ctrl+s+"));
    PRINT_KEY_SEQ(KeySequence(L" cTrL + f "));
    PRINT_KEY_SEQ(KeySequence(L"ctrl+s+s"));

    DIVIDING_LINE_1('#');

    PRINT_KEY_SEQ(KeySequence(KeySequence(L"Ctrl+F1").ToHotKey()));
    PRINT_KEY_SEQ(KeySequence(KeySequence(L"Alt+S").ToAccel()));

    DIVIDING_LINE_1('~');

    std::unordered_set<KeySequence> keySequenceSet;
    KeySequence ctrlS(L"Ctrl+S");
    KeySequence ctrlS2(L'S', HOTKEYF_CONTROL);
    keySequenceSet.insert(ctrlS);
    if (keySequenceSet.find(ctrlS2) != keySequenceSet.cend())
        std::cout << "Duplicated key sequence!\n";

    DIVIDING_LINE_1('-');

    AccelTable table;
    table[ID_COPY] = KeySequence::FromString(L"Ctrl+C", L"+");
    table[ID_PASTE] = KeySequence(L"Ctrl+S");

    PrintAccelTable(table);

    HACCEL hAccel = table.CreateAcceleratorTable();

    AccelTable table2(hAccel);
    table2[ID_EXIT] = KeySequence(L"Ctrl+w");

    DestroyAcceleratorTable(hAccel);

    PrintAccelTable(table2);

    return 0;
}
