// 2016-11-26T15:23+08:00
#ifndef HOTKEYHELPER_H_
#define HOTKEYHELPER_H_

#include "Win32Cmn.h"

struct HotKey {
    WORD wVk;
    WORD wModifiers;
};

bool IsValidHotKeyModifiers(WORD wHotKeyModifiers);
bool IsValidHotKey(WORD wVk, WORD wModifiers);
bool IsValidHotKey(HotKey hotKey);

#endif // HOTKEYHELPER_H_
