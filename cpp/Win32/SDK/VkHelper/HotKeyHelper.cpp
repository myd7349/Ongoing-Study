#include "HotKeyHelper.h"

#include "../../../bitsutils.hpp"
#include "VkHelper.h"


bool IsValidHotKeyModifiers(WORD wHotKeyModifiers)
{
    return ClearBits(wHotKeyModifiers,
        static_cast<WORD>(HOTKEYF_CONTROL | HOTKEYF_ALT | HOTKEYF_SHIFT | HOTKEYF_EXT)) == 0;
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
