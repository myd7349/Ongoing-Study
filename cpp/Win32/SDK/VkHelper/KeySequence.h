// 2016-11-26T15:13+08:00
#ifndef KEYSEQUENCE_H_
#define KEYSEQUENCE_H_

#include "HotKeyHelper.h"
#include "VkHelper.h"


class KeySequence {
public:
    KeySequence(VkUtils::vk_t vk, bool ctrl, bool shift, bool alt);
    explicit KeySequence(const std::wstring &keySequence, const std::wstring &delimiter = L"");
    explicit KeySequence(ACCEL accel);
    explicit KeySequence(HotKey hotKey);
    explicit KeySequence(WORD wVirtualKey = 0, WORD wHotKeyModifiers = 0);

    bool IsValid() const;
    std::wstring ToString(const std::wstring &delimiter = L"") const;
    ACCEL ToAccel() const;
    HotKey ToHotKey() const;

private:
    void CreateFromString(const std::wstring &keySequence, const std::wstring &delimiter);
    void CreateFromHotKey(WORD wVirtualKey, WORD wHotKeyModifiers);

    VkUtils::vk_t vk_;
    bool ctrl_;
    bool shift_;
    bool alt_;

    static std::wstring plus_;
};

#endif // KEYSEQUENCE_H_
