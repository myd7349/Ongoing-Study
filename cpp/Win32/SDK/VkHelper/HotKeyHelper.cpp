#include "HotKeyHelper.h"

#include "../../../bitsutils.hpp"
#include "VkHelper.h"


bool IsValidHotKeyModifiers(WORD wHotKeyModifiers)
{
    ClearBits(wHotKeyModifiers, (WORD)HOTKEYF_CONTROL);
    ClearBits(wHotKeyModifiers, (WORD)HOTKEYF_ALT);
    ClearBits(wHotKeyModifiers, (WORD)HOTKEYF_SHIFT);
    ClearBits(wHotKeyModifiers, (WORD)HOTKEYF_EXT);
    return wHotKeyModifiers == 0;
}

bool IsValidHotKey(WORD wVk, WORD wModifiers)
{
    return VkUtils::IsKnownVkCode(wVk)
        && !VkUtils::IsModifier(wVk)
        && IsValidHotKeyModifiers(wModifiers);
}

bool IsValidHotKey(HotKey hotKey)
{
    return IsValidHotKey(hotKey.wVk, hotKey.wModifiers);
}
