#include "VkHelper.h"

#include <cassert>
#include <stddef.h>
#include <unordered_map>
#include <vector>


#include "../../../common.h"
#include "../../../strutils.hpp"

#include "VkCodesTable.inl"

namespace {
    typedef std::unordered_map<std::wstring, VkUtils::vk_t> VkNameToCodeMap;

    class VkCodeHelper_ {
    public:
        VkCodeHelper_() {
            InitializeVkCodeMap();
        }

        VkUtils::vk_t operator[](const std::wstring &keyName) {
            if (keyName.empty())
                return VkUtils::InvalidVkCode;

            std::wstring key = ToLower(keyName);
            VkNameToCodeMap::const_iterator it = vkcode_map_.find(key);
            if (it != vkcode_map_.cend())
                return it->second;

            return VkUtils::InvalidVkCode;
        }

    private:
        void InitializeVkCodeMap() {
            std::wstring keyName;

            for (size_t i = 0; i < ARRAYSIZE(VkCodesTable); ++i) {
                if (VkUtils::IsKnownVkCode(VkCodesTable[i])) {
                    keyName = VkUtils::Detail::GetVkName(VkCodesTable[i]);
                    if (!keyName.empty()) {
                        ToLowerInPlace(keyName);
                        vkcode_map_[keyName] = static_cast<VkUtils::vk_t>(VkCodesTable[i]);
                    }
                }
            }
        }

        VkNameToCodeMap vkcode_map_;
    } VkCodeMap_;
}

namespace VkUtils {
    bool IsKnownVkCode(vk_t vkcode)
    {
        bool inRange = vkcode > 0 && vkcode < ARRAYSIZE(VkCodesTable);

        if (!inRange)
            return false;

        return VkCodesTable[static_cast<int>(vkcode)] == static_cast<unsigned char>(vkcode);
    }

    std::wstring GetVkName(vk_t vkcode, bool isExtended)
    {
        return Detail::GetVkName(vkcode, isExtended);
    }

    // I didn't find the counterpart of GetKeyNameTextW which can get the virtual
    // key code from input key name. So DIY one!
    vk_t GetVkCode(const std::wstring &keyName)
    {
        return VkCodeMap_[keyName];
    }

    namespace Detail {
        std::wstring GetVkName(vk_t vkcode, bool isExtended)
        {
            bool isKnownVkCode = IsKnownVkCode(vkcode);
            if (!isKnownVkCode)
                return std::wstring();

            // MFC: CHotKeyCtrl::GetKeyName
            LONG lScan = ::MapVirtualKey(vkcode, 0) << 16;

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
    }
}
