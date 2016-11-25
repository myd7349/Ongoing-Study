#include "VkHelper.h"

#include <cassert>
#include <functional>
#include <memory>
#include <stddef.h>
#include <unordered_map>
#include <vector>


#include "../../../common.h"
#include "../../../strutils.hpp"

#include "VkCodesTable.inl"

namespace {
    struct WStringIHashFunctor {
        size_t operator()(const std::wstring &key) const {
            return hash_(ToLower(key));
        }

    private:
        std::hash<std::wstring> hash_;
    };

    struct WStringICompareFunctor {
        bool operator() (const std::wstring &lhs, const std::wstring &rhs) const {
            return StringICompare(lhs, rhs);
        }
    };

    typedef std::unordered_map<std::wstring,
                               VkUtils::vk_t,
                               WStringIHashFunctor,
                               WStringICompareFunctor> VkNameToCodeMap;
    typedef std::unordered_map<VkUtils::vk_t, std::wstring> VkCodeToNameMap;

    class VkCodeHelper_ {
    public:
        VkCodeHelper_() {
            InitializeVkCodeMap();
        }

        VkUtils::vk_t operator[](const std::wstring &keyName) {
            if (keyName.empty())
                return VkUtils::InvalidVkCode;

            VkNameToCodeMap::const_iterator it = vkname_map_.find(keyName);
            if (it != vkname_map_.cend())
                return it->second;

            return VkUtils::InvalidVkCode;
        }

        const std::wstring &operator[](VkUtils::vk_t vk) {
            VkCodeToNameMap::const_iterator it = vkcode_map_.find(vk);
            if (it != vkcode_map_.cend())
                return it->second;

            return dummy_;
        }

    private:
        void InitializeVkCodeMap() {
            std::wstring keyName;

            for (size_t i = 0; i < ARRAYSIZE(VkCodesTable); ++i) {
                if (VkUtils::IsKnownVkCode(VkCodesTable[i])) {
                    keyName = VkUtils::Detail::GetVkName(VkCodesTable[i]);
                    if (!keyName.empty()) {
                        // 1. Build Name=>Code Map;
                        if (vkname_map_.find(keyName) == vkname_map_.cend()) // VK_CONTROL, VK_LCONTROL, VK_RCONTROL => VK_CONTROL
                            vkname_map_[keyName] = VkCodesTable[i];

                        // 2. Build Code=>Name Map;
                        vkcode_map_[VkCodesTable[i]] = keyName;
                    }
                }
            }
        }

        VkNameToCodeMap vkname_map_;
        VkCodeToNameMap vkcode_map_;

        std::wstring dummy_;
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
        return VkCodeMap_[vkcode];
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
                return L"";

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
