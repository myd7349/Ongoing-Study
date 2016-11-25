#include "VkHelper.h"

#include <cassert>
#include <stddef.h>
#include <vector>


#include "../../../common.h"

#include "VkCodesTable.inl"


namespace VkUtils {
    bool IsKnownVkCode(vk_t vkcode)
    {
        bool inRange = vkcode > 0 && vkcode < ARRAYSIZE(VkCodesTable);

        assert(inRange);
        if (!inRange)
            return false;

        return VkCodesTable[static_cast<int>(vkcode)] == static_cast<unsigned char>(vkcode);
    }

    std::wstring GetVkName(vk_t vkcode, bool isExtended)
    {
        bool isKnownVkCode = IsKnownVkCode(vkcode);
        if (!isKnownVkCode)
            return std::wstring();

        // MFC: CHotKeyCtrl::GetKeyName
        LONG lScan = MapVirtualKey(vkcode, 0) << 16;

        if (isExtended)
            lScan |= 0x01000000L;

        size_t bufferLength = 64;
        std::vector<wchar_t> stringBuffer;
        size_t length = 0;

        do {
            bufferLength *= 2;
            stringBuffer.resize(bufferLength);
            LPWSTR psz = stringBuffer.data();
            length = ::GetKeyNameTextW(lScan, psz, bufferLength);
        } while (length == bufferLength);

        return std::wstring(stringBuffer.cbegin(), stringBuffer.cbegin() + length);
    }

    vk_t GetVkCode(std::wstring keyName)
    {
        return 0;
    }
}
