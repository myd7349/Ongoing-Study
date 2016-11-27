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

    void Clear();
    bool Set(VkUtils::vk_t vk, bool ctrl, bool shift, bool alt);
    bool Set(const std::wstring &keySequence, const std::wstring &delimiter = L"");
    bool Set(ACCEL accel);
    bool Set(HotKey hotKey);
    bool Set(WORD wVirtualKey, WORD wHotKeyModifiers);

    bool IsEmpty() const;
    bool IsValid() const;
    std::wstring ToString(const std::wstring &delimiter = L"") const;
    ACCEL ToAccel() const;
    HotKey ToHotKey() const;

private:
    bool CreateFromString(const std::wstring &keySequence, const std::wstring &delimiter);

    VkUtils::vk_t vk_;
    bool ctrl_;
    bool shift_;
    bool alt_;

    static std::wstring plus_;
};

namespace std {
    template <>
    struct hash<KeySequence> {
        size_t operator()(const KeySequence &keySequence) const {
            return hash<HotKey>()(keySequence.ToHotKey());
        }
    };
}

inline bool operator==(const KeySequence &lhs, const KeySequence &rhs)
{
    return lhs.ToHotKey() == rhs.ToHotKey();
}

inline bool operator!=(const KeySequence &lhs, const KeySequence &rhs)
{
    return !operator==(lhs,rhs);
}

#endif // KEYSEQUENCE_H_
