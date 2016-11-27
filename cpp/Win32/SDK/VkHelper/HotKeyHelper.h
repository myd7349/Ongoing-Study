// 2016-11-26T15:23+08:00
#ifndef HOTKEYHELPER_H_
#define HOTKEYHELPER_H_

#include <functional>

#include "Win32Cmn.h"

struct HotKey {
    WORD wVk;
    WORD wModifiers;
};

bool IsValidHotKeyModifiers(WORD wHotKeyModifiers);
bool IsValidHotKey(WORD wVk, WORD wModifiers);
bool IsValidHotKey(HotKey hotKey);

namespace std {
    template <>
    struct hash<HotKey> {
        size_t operator()(const HotKey &hotKey) const {
            // MSDN:
            // WM_SETHOTKEY
            // wParam
            //     The low-order word specifies the virtual-key code to associate with the window.
            //     The high-order word can be one or more of the following values.
            return hash<LONG>()(MAKELONG(hotKey.wVk, hotKey.wModifiers));
        }
    };
}

inline bool operator==(const HotKey &lhs, const HotKey &rhs)
{
    return (lhs.wVk == rhs.wVk) && (lhs.wModifiers == rhs.wModifiers);
}

inline bool operator!=(const HotKey &lhs, const HotKey &rhs)
{
    return !operator==(lhs,rhs);
}

#endif // HOTKEYHELPER_H_

// References:
// [How to specialize std::hash<Key>::operator() for user-defined type in unordered containers?](http://stackoverflow.com/questions/8157937/how-to-specialize-stdhashkeyoperator-for-user-defined-type-in-unordered)
// http://en.cppreference.com/w/cpp/utility/hash
// [Operator overloading](http://stackoverflow.com/questions/4421706/operator-overloading)
