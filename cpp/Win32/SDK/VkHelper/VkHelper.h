// 2016-11-25T09:02+08:00
#ifndef VKHELPER_H_
#define VKHELPER_H_

#define STRICT (1)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <string>

namespace VkUtils {
    typedef WORD vk_t;

    const vk_t InvalidVkCode = 0;

    bool IsKnownVkCode(vk_t vkcode);

    std::wstring GetVkName(vk_t vkcode, bool isExtended = false);
    vk_t GetVkCode(const std::wstring &keyName);
}

#endif // VKHELPER_H_
