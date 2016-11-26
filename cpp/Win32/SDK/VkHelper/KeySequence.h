// 2016-11-26T15:13+08:00
#ifndef KEYSEQUENCE_H_
#define KEYSEQUENCE_H_

#include "HotKeyHelper.h"
#include "VkHelper.h"


class KeySequence {
public:
    explicit KeySequence(VkUtils::vk_t vk = 0);
    explicit KeySequence(const std::wstring &keySequence, const std::wstring &delimiter = L"");
    explicit KeySequence(ACCEL accel);
    explicit KeySequence(HotKey hotKey);
    KeySequence(WORD wVirtualKey, WORD wHotKeyModifiers);

    bool IsValid() const;
    std::wstring ToString() const;
    ACCEL ToAccel() const;
    HotKey ToHotKey() const;

private:
    void CreateFromString(const std::wstring &keySequence, const std::wstring &delimiter);
    void CreateFromHotKey(WORD wVirtualKey, WORD wHotKeyModifiers);

    bool ctrl_;
    bool shift_;
    bool alt_;
    VkUtils::vk_t vk_;

    static std::wstring plus_;
};

#endif // KEYSEQUENCE_H_
