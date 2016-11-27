#include "KeySequence.h"

#include <vector>

#include "../../../bitsutils.hpp"
#include "../../../join.hpp"
#include "../../../split.hpp"
#include "AccelHelper.h"


std::wstring KeySequence::plus_ = L"+";


KeySequence::KeySequence(VkUtils::vk_t vk, bool ctrl, bool shift, bool alt)
    : vk_(0), ctrl_(false), shift_(false), alt_(false)
{
    Set(vk, ctrl, shift, alt);
}

KeySequence::KeySequence(const std::wstring &keySequence, const std::wstring &delimiter)
    : vk_(0), ctrl_(false), shift_(false), alt_(false)
{
    Set(keySequence, delimiter);
}

KeySequence::KeySequence(ACCEL accel)
    : vk_(0), ctrl_(false), shift_(false), alt_(false)
{
    Set(accel);
}

KeySequence::KeySequence(HotKey hotKey)
    : vk_(0), ctrl_(false), shift_(false), alt_(false)
{
    Set(hotKey);
}

KeySequence::KeySequence(WORD wVirtualKey, WORD wHotKeyModifiers)
    : vk_(0), ctrl_(false), shift_(false), alt_(false)
{
    Set(wVirtualKey, wHotKeyModifiers);
}

void KeySequence::Clear()
{
    vk_ = 0;
    ctrl_ = shift_ = alt_ = false;
}

bool KeySequence::Set(VkUtils::vk_t vk, bool ctrl, bool shift, bool alt)
{
    bool ok = VkUtils::IsKnownVkCode(vk) && !VkUtils::IsModifier(vk);
    //Assert(ok, "Invalid virtual key code!");
    if (ok) {
        vk_ = vk;
        ctrl_ = ctrl;
        shift_ = shift;
        alt_ = alt;
    } else {
        Clear();
    }

    return ok;
}

bool KeySequence::Set(const std::wstring &keySequence, const std::wstring &delimiter)
{
    bool ok = CreateFromString(keySequence, delimiter);
    if (!ok)
        Clear();

    return ok;
}

bool KeySequence::Set(ACCEL accel)
{
    bool ok = IsValidAccel(accel);
    Assert(ok, "Invalid ACCEL!");
    if (ok) {
        vk_ = accel.key;
        ctrl_ = IsBitsSet<int>(accel.fVirt, FCONTROL);
        shift_ = IsBitsSet<int>(accel.fVirt, FSHIFT);
        alt_ = IsBitsSet<int>(accel.fVirt, FALT);
    } else {
        Clear();
    }

    return ok;
}

bool KeySequence::Set(HotKey hotKey)
{
    return Set(hotKey.wVk, hotKey.wModifiers);
}

bool KeySequence::Set(WORD wVirtualKey, WORD wHotKeyModifiers)
{
    bool ok = IsValidHotKey(wVirtualKey, wHotKeyModifiers);
    //Assert(ok, "Invalid hot key!");
    if (ok) {
        vk_ = wVirtualKey;
        ctrl_ = IsBitsSet<int>(wHotKeyModifiers, HOTKEYF_CONTROL);
        shift_ = IsBitsSet<int>(wHotKeyModifiers, HOTKEYF_SHIFT);
        alt_ = IsBitsSet<int>(wHotKeyModifiers, HOTKEYF_ALT);
    } else {
        Clear();
    }

    return ok;
}

bool KeySequence::IsValid() const
{
    return VkUtils::IsKnownVkCode(vk_) && !VkUtils::IsModifier(vk_);
}

std::wstring KeySequence::ToString(const std::wstring &delimiter) const
{
    if (!IsValid())
        return L"";

    std::vector<std::wstring> keys;
    keys.reserve(4);

    if (ctrl_)
        keys.push_back(VkUtils::GetVkName(VK_CONTROL));
    if (shift_)
        keys.push_back(VkUtils::GetVkName(VK_SHIFT));
    if (alt_)
        keys.push_back(VkUtils::GetVkName(VK_MENU));

    keys.push_back(VkUtils::GetVkName(vk_));

    return join(keys.cbegin(), keys.cend(), delimiter.empty() ? plus_ : delimiter);
}

ACCEL KeySequence::ToAccel() const
{
    ACCEL accel;

    if (IsValid()) {
        accel.key = vk_;

        if (ctrl_)
            SetBits(accel.fVirt, static_cast<BYTE>(FCONTROL));
        if (shift_)
            SetBits(accel.fVirt, static_cast<BYTE>(FSHIFT));
        if (alt_)
            SetBits(accel.fVirt, static_cast<BYTE>(FALT));
    }

    return accel;
}

HotKey KeySequence::ToHotKey() const
{
    HotKey hotKey;

    if (IsValid()) {
        hotKey.wVk = vk_;

        if (ctrl_)
            SetBits(hotKey.wModifiers, static_cast<WORD>(HOTKEYF_CONTROL));
        if (shift_)
            SetBits(hotKey.wModifiers, static_cast<WORD>(HOTKEYF_SHIFT));
        if (alt_)
            SetBits(hotKey.wModifiers, static_cast<WORD>(HOTKEYF_ALT));
    }

    return hotKey;
}

bool KeySequence::CreateFromString(const std::wstring &keySequence, const std::wstring &delimiter)
{
    std::vector<std::wstring> keys = split(keySequence, delimiter.empty() ? plus_ : delimiter);
    if (keys.empty() || keys.size() > 4)
        return false;

    bool isCtrlSet = false;
    bool isShiftSet = false;
    bool isAltSet = false;
    bool isVkSet = false;
    VkUtils::vk_t code = 0, vk = 0;

    for (std::vector<std::wstring>::const_iterator it = keys.cbegin(); it != keys.cend(); ++it) {
        code = VkUtils::GetVkCode(*it);
        if (!VkUtils::IsKnownVkCode(code))
            return false;

        switch (code) {
        case VK_CONTROL:
            if (!isCtrlSet)
                isCtrlSet = true;
            else // Found duplicate control key
                return false;
            break;
        case VK_SHIFT:
            if (!isShiftSet)
                isShiftSet = true;
            else
                return false;
            break;
        case VK_MENU:
            if (!isAltSet)
                isAltSet = true;
            else
                return false;
            break;
        default:
            if (!isVkSet) {
                isVkSet = true;
                vk = code;
            } else {
                return false;
            }
            break;
        }
    }

    if (!isVkSet)
        return false;

    vk_ = vk;
    ctrl_ = isCtrlSet;
    shift_ = isShiftSet;
    alt_ = isAltSet;
    return true;
}

