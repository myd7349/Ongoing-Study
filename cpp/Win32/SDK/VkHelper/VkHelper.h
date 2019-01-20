// 2016-11-25T09:02+08:00
#ifndef VKHELPER_H_
#define VKHELPER_H_


#include <string>

#include "Win32Cmn.h"


namespace VkUtils {
    typedef WORD vk_t;

    const vk_t InvalidVkCode = 0;

    bool IsKnownVkCode(vk_t vkcode);
    bool IsModifier(vk_t vkcode);
    std::wstring GetVkName(vk_t vkcode);
    vk_t GetVkCode(const std::wstring &keyName);

    namespace Detail {
        std::wstring GetVkName(vk_t vkcode, bool isExtended = false);
    }
}

#endif // VKHELPER_H_
